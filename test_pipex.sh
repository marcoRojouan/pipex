#!/bin/bash

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PIPEX="./pipex"
TEST_COUNT=0
PASS_COUNT=0
FAIL_COUNT=0

# Fonction pour afficher les résultats
print_test() {
    local test_name=$1
    local status=$2
    TEST_COUNT=$((TEST_COUNT + 1))
    
    if [ "$status" = "PASS" ]; then
        echo -e "${GREEN}✓${NC} Test $TEST_COUNT: $test_name"
        PASS_COUNT=$((PASS_COUNT + 1))
    else
        echo -e "${RED}✗${NC} Test $TEST_COUNT: $test_name"
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
}

# Fonction pour comparer les résultats
compare_outputs() {
    local test_name=$1
    local shell_out=$2
    local pipex_out=$3
    
    if diff -q "$shell_out" "$pipex_out" > /dev/null 2>&1; then
        print_test "$test_name" "PASS"
    else
        print_test "$test_name" "FAIL"
        echo -e "${YELLOW}  Expected:${NC}"
        cat "$shell_out" 2>/dev/null || echo "(fichier vide ou erreur)"
        echo -e "${YELLOW}  Got:${NC}"
        cat "$pipex_out" 2>/dev/null || echo "(fichier vide ou erreur)"
    fi
}

# Vérifier que pipex existe
if [ ! -f "$PIPEX" ]; then
    echo -e "${RED}Erreur: $PIPEX n'existe pas. Compile d'abord ton projet.${NC}"
    exit 1
fi

echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}   TESTS PIPEX - 42 PROJECT${NC}"
echo -e "${BLUE}================================${NC}\n"

# Créer un fichier de test
cat << EOF > infile
Bonjour 42
Ceci est un test
de pipex
avec plusieurs lignes
pour tester
les pipes
EOF

echo -e "${YELLOW}📁 Fichiers de test créés${NC}\n"

# ============================================
# TESTS BASIQUES
# ============================================
echo -e "${BLUE}=== Tests Basiques ===${NC}"

# Test 1: cat | wc -l
< infile cat | wc -l > shell_out
$PIPEX infile "cat" "wc -l" pipex_out
compare_outputs "cat | wc -l" shell_out pipex_out

# Test 2: grep | wc -l
< infile grep test | wc -l > shell_out
$PIPEX infile "grep test" "wc -l" pipex_out
compare_outputs "grep test | wc -l" shell_out pipex_out

# Test 3: cat | cat
< infile cat | cat > shell_out
$PIPEX infile "cat" "cat" pipex_out
compare_outputs "cat | cat" shell_out pipex_out

# Test 4: ls | grep test (commandes qui produisent du contenu)
touch test1.txt test2.txt autre.txt
< infile ls | grep test > shell_out 2>&1
$PIPEX infile "ls" "grep test" pipex_out 2>&1
compare_outputs "ls | grep test" shell_out pipex_out

# ============================================
# TESTS AVEC OPTIONS
# ============================================
echo -e "\n${BLUE}=== Tests avec Options ===${NC}"

# Test 5: grep avec options
< infile grep -i TEST | wc -l > shell_out
$PIPEX infile "grep -i TEST" "wc -l" pipex_out
compare_outputs "grep -i TEST | wc -l" shell_out pipex_out

# Test 6: cat -e
< infile cat -e | head -n 3 > shell_out
$PIPEX infile "cat -e" "head -n 3" pipex_out
compare_outputs "cat -e | head -n 3" shell_out pipex_out

# Test 7: wc avec plusieurs options
< infile cat | wc -lwc > shell_out
$PIPEX infile "cat" "wc -lwc" pipex_out
compare_outputs "cat | wc -lwc" shell_out pipex_out

# ============================================
# TESTS D'ERREURS - FICHIERS
# ============================================
echo -e "\n${BLUE}=== Tests d'Erreurs - Fichiers ===${NC}"

# Test 8: Infile inexistant
$PIPEX fichier_inexistant "cat" "wc -l" pipex_out 2> pipex_err
pipex_exit=$?
if grep -q "No such file or directory" pipex_err 2>/dev/null; then
    print_test "Infile inexistant (message d'erreur)" "PASS"
else
    print_test "Infile inexistant (pas de message d'erreur)" "FAIL"
fi

# Test 9: Infile sans droits de lecture
touch no_read_file
chmod 000 no_read_file
$PIPEX no_read_file "cat" "wc -l" pipex_out 2> pipex_err
pipex_exit=$?
if grep -q "Permission denied" pipex_err 2>/dev/null; then
    print_test "Infile sans droits de lecture" "PASS"
else
    print_test "Infile sans droits de lecture" "FAIL"
fi
chmod 644 no_read_file 2>/dev/null

# Test 10: Outfile dans dossier sans droits
mkdir -p no_write_dir
chmod 000 no_write_dir
$PIPEX infile "cat" "wc -l" no_write_dir/outfile 2> /dev/null
if [ $? -ne 0 ]; then
    print_test "Outfile dans dossier sans droits" "PASS"
else
    print_test "Outfile dans dossier sans droits" "FAIL"
fi
chmod 755 no_write_dir

# ============================================
# TESTS D'ERREURS - COMMANDES
# ============================================
echo -e "\n${BLUE}=== Tests d'Erreurs - Commandes ===${NC}"

# Test 11: Première commande invalide
$PIPEX infile "commande_bidon" "wc -l" pipex_out 2> pipex_err
pipex_exit=$?
if [ $pipex_exit -eq 127 ]; then
    print_test "Première commande invalide (exit 127)" "PASS"
else
    print_test "Première commande invalide (exit $pipex_exit)" "FAIL"
fi

# Test 12: Deuxième commande invalide
$PIPEX infile "cat" "commande_bidon" pipex_out 2> pipex_err
pipex_exit=$?
if [ $pipex_exit -eq 127 ]; then
    print_test "Deuxième commande invalide (exit 127)" "PASS"
else
    print_test "Deuxième commande invalide (exit $pipex_exit)" "FAIL"
fi

# Test 13: Les deux commandes invalides
$PIPEX infile "bidon1" "bidon2" pipex_out 2> pipex_err
pipex_exit=$?
if [ $pipex_exit -eq 127 ]; then
    print_test "Deux commandes invalides (exit 127)" "PASS"
else
    print_test "Deux commandes invalides (exit $pipex_exit)" "FAIL"
fi

# Test 14: Commande vide
$PIPEX infile "" "wc -l" pipex_out 2> pipex_err
if [ $? -ne 0 ]; then
    print_test "Commande vide" "PASS"
else
    print_test "Commande vide" "FAIL"
fi

# ============================================
# TESTS AVEC /bin/ et /usr/bin/
# ============================================
echo -e "\n${BLUE}=== Tests avec Chemins Absolus ===${NC}"

# Test 15: Chemin absolu /bin/cat
< infile /bin/cat | wc -l > shell_out
$PIPEX infile "/bin/cat" "wc -l" pipex_out
compare_outputs "/bin/cat | wc -l" shell_out pipex_out

# Test 16: Chemin absolu invalide
$PIPEX infile "/bin/commande_inexistante" "wc -l" pipex_out 2> pipex_err
if [ $? -ne 0 ]; then
    print_test "Chemin absolu invalide" "PASS"
else
    print_test "Chemin absolu invalide" "FAIL"
fi

# ============================================
# TESTS DE PERMISSIONS
# ============================================
echo -e "\n${BLUE}=== Tests de Permissions ===${NC}"

# Test 17: Outfile existant avec permissions
touch existing_outfile
echo "ancien contenu" > existing_outfile
< infile cat | wc -l > shell_out
$PIPEX infile "cat" "wc -l" existing_outfile
if diff -q shell_out existing_outfile > /dev/null 2>&1; then
    print_test "Écrasement outfile existant" "PASS"
else
    print_test "Écrasement outfile existant" "FAIL"
fi

# Test 18: Outfile sans droits d'écriture
touch readonly_outfile
chmod 444 readonly_outfile
$PIPEX infile "cat" "wc -l" readonly_outfile 2> /dev/null
if [ $? -ne 0 ]; then
    print_test "Outfile sans droits d'écriture" "PASS"
else
    print_test "Outfile sans droits d'écriture" "FAIL"
fi
chmod 644 readonly_outfile

# ============================================
# TESTS DE STRESS
# ============================================
echo -e "\n${BLUE}=== Tests de Stress ===${NC}"

# Test 19: Gros fichier
seq 1 10000 > bigfile
< bigfile cat | wc -l > shell_out
$PIPEX bigfile "cat" "wc -l" pipex_out
compare_outputs "Gros fichier (10000 lignes)" shell_out pipex_out

# Test 20: Fichier vide
touch emptyfile
< emptyfile cat | wc -l > shell_out
$PIPEX emptyfile "cat" "wc -l" pipex_out
compare_outputs "Fichier vide" shell_out pipex_out

# Test 21: Commandes qui ne lisent pas stdin
< infile echo "test" | cat > shell_out
$PIPEX infile "echo test" "cat" pipex_out
compare_outputs "echo test | cat" shell_out pipex_out

# ============================================
# TEST VALGRIND (optionnel)
# ============================================
echo -e "\n${BLUE}=== Test Valgrind ===${NC}"
if command -v valgrind &> /dev/null; then
    valgrind --leak-check=full --errors-for-leak-kinds=definite --error-exitcode=1 \
        $PIPEX infile "cat" "wc -l" pipex_out > /dev/null 2> valgrind_out
    
    if [ $? -eq 0 ]; then
        print_test "Valgrind - Pas de leaks" "PASS"
    else
        print_test "Valgrind - Pas de leaks" "FAIL"
        echo -e "${YELLOW}  Voir valgrind_out pour les détails${NC}"
    fi
else
    echo -e "${YELLOW}⚠ Valgrind non installé, test ignoré${NC}"
fi

# ============================================
# TEST PROCESSUS ZOMBIES
# ============================================
echo -e "\n${BLUE}=== Test Processus Zombies ===${NC}"
$PIPEX infile "cat" "wc -l" pipex_out &
PID=$!
sleep 1
ZOMBIES=$(ps aux | grep defunct | grep -v grep | wc -l)
wait $PID

if [ $ZOMBIES -eq 0 ]; then
    print_test "Pas de processus zombies" "PASS"
else
    print_test "Pas de processus zombies ($ZOMBIES trouvés)" "FAIL"
fi

# ============================================
# NETTOYAGE
# ============================================
echo -e "\n${BLUE}=== Nettoyage ===${NC}"
rm -f infile shell_out pipex_out shell_err pipex_err
rm -f test1.txt test2.txt autre.txt
rm -f no_read_file existing_outfile readonly_outfile
rm -f bigfile emptyfile valgrind_out
rm -rf no_write_dir

# ============================================
# RÉSUMÉ
# ============================================
echo -e "\n${BLUE}================================${NC}"
echo -e "${BLUE}          RÉSUMÉ${NC}"
echo -e "${BLUE}================================${NC}"
echo -e "Total de tests: ${TEST_COUNT}"
echo -e "${GREEN}Tests réussis: ${PASS_COUNT}${NC}"
echo -e "${RED}Tests échoués: ${FAIL_COUNT}${NC}"

if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "\n${GREEN}🎉 Tous les tests sont passés ! Ton pipex est prêt pour la correction !${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Certains tests ont échoué. Vérifie les erreurs ci-dessus.${NC}"
    exit 1
fi