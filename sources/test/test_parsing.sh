#!/bin/bash

# Couleurs pour un affichage plus clair
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Nom de votre exécutable (à modifier si nécessaire)
EXECUTABLE="./test_parsing"

# Durée maximale d'exécution pour chaque test (en secondes)
TIMEOUT=10

# Vérifier si l'exécutable existe
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Erreur: L'exécutable '$EXECUTABLE' n'existe pas.${NC}"
    echo "Compilez d'abord votre programme avec 'make'."
    exit 1
fi

# Vérifier si la commande timeout est disponible
if ! command -v timeout &> /dev/null; then
    echo -e "${RED}Erreur: La commande 'timeout' n'est pas disponible.${NC}"
    echo "Cette commande est nécessaire pour gérer les timeouts."
    exit 1
fi

# Compteur de tests réussis
PASSED=0
TOTAL=20
TIMEOUTS=0

# Fonction pour exécuter un test
run_test() {
    local test_num=$1
    
    echo -e "${BLUE}Exécution du test $test_num...${NC}"
    
    # Exécuter le test avec timeout et capturer la sortie
    output=$(timeout $TIMEOUT bash -c "echo '$test_num' | $EXECUTABLE 2>&1")
    
    # Vérifier le code de retour de timeout
    if [ $? -eq 124 ]; then
        echo -e "${RED}Test $test_num: TIMEOUT (> $TIMEOUT secondes)${NC}"
        TIMEOUTS=$((TIMEOUTS + 1))
        return
    fi
    
    # Vérifier si le test a réussi
    if echo "$output" | grep -q "✅"; then
        echo -e "${GREEN}Test $test_num: RÉUSSI${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}Test $test_num: ÉCHOUÉ${NC}"
        echo -e "${YELLOW}Détails:${NC}"
        echo "$output" | grep -v "Choisissez un cas" | tail -5
    fi
}

echo -e "${YELLOW}=== Exécution des tests pour minishell ===${NC}"

# Tests valides (1-5)
echo -e "${YELLOW}=== Tests de commandes valides (1-5) ===${NC}"
for i in {1..5}; do
    run_test $i
done

# Tests d'erreurs (6-20)
echo -e "${YELLOW}=== Tests de cas d'erreurs (6-20) ===${NC}"
for i in {6..20}; do
    run_test $i
done

# Calculer le pourcentage de réussite
PERCENTAGE=$(awk "BEGIN {printf \"%.1f\", ($PASSED / $TOTAL) * 100}")

# Afficher le résumé
echo -e "${YELLOW}=== Résumé des tests ===${NC}"
echo -e "Tests réussis: ${GREEN}$PASSED/$TOTAL${NC} (${GREEN}$PERCENTAGE%${NC})"

if [ $TIMEOUTS -gt 0 ]; then
    echo -e "Tests en timeout: ${RED}$TIMEOUTS${NC}"
fi

# Vérifier si tous les tests ont réussi
if [ $PASSED -eq $TOTAL ]; then
    echo -e "${GREEN}ALL TESTS PASSED${NC}"
    exit 0
else
    echo -e "${RED}$((TOTAL - PASSED)) test(s) ont échoué${NC}"
    exit 1
fi