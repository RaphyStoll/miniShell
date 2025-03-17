#!/bin/bash

# Couleurs
BLUE='\033[1;34m'
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # Reset couleur

# 🔹 Liste des tests à exécuter
TESTS=(
    "echo hello && ls"
    "echo hello&&ls"
    "echo 'hello && ls'"
    "echo \"hello&&ls\""
    "echo \"hello\"&&ls"
    "echo hello >file"
    "echo hello>file"
    "(echo hello) && ls"
    "echo \"hello && ls"  # ❌ Quote non fermée
    "echo hello && (ls"   # ❌ Parenthèse non fermée
    "echo | ls"
    "echo || ls"
    "echo a>b"
    "echo 'hello'world"
    "echo 'hello world"   # ❌ Quote non fermée
)

EXPECTED_FILE="expected_output.txt"
ACTUAL_FILE="actual_output.txt"

# Vérifie si le fichier de sortie attendue existe
if [ ! -f "$EXPECTED_FILE" ]; then
    echo -e "${RED}❌ ERREUR : Le fichier '$EXPECTED_FILE' avec les sorties attendues n'existe pas.${NC}"
    exit 1
fi

# Fonction pour associer les types de tokens
get_token_type() {
    case $1 in
        0) echo "WORD" ;;
        1) echo "PIPE" ;;
        2) echo "REDIRECT_IN" ;;
        3) echo "REDIRECT_OUT" ;;
        4) echo "HEREDOC" ;;
        5) echo "APPEND" ;;
        6) echo "AND" ;;
        7) echo "OR" ;;
        8) echo "O_PARENTHESIS" ;;
        9) echo "C_PARENTHESIS" ;;
        *) echo "UNKNOWN" ;;
    esac
}

# 🔹 Exécuter chaque test
echo -e "${BLUE}🟡 Running lexer tests...${NC}"
> "$ACTUAL_FILE"  # Vide le fichier actuel

for i in "${!TESTS[@]}"; do
    test="${TESTS[$i]}"
    echo -e "\n${BLUE}🔵 Test $((i+1)) : \"$test\"${NC}"
    echo -e "\nTest: \"$test\"" >> "$ACTUAL_FILE"

    # Exécute le programme et stocke le résultat
    OUTPUT=$(./test_lexing "$test")
    echo "$OUTPUT" >> "$ACTUAL_FILE"

    # Vérification si erreur
    if echo "$OUTPUT" | grep -q "Syntax error"; then
        echo -e "${RED}❌ Erreur détectée !${NC}"
    else
        echo -e "${GREEN}✅ Succès !${NC}"
    fi

    # Extraction des tokens et conversion en types lisibles
    TOKENS=$(echo "$OUTPUT" | grep -E 'Token:' | awk -F '[()]' '{print $2}')
    FORMATTED_TOKENS=""
    for token in $TOKENS; do
        FORMATTED_TOKENS+=" $(get_token_type "$token")"
    done

    # Affichage propre des tokens convertis
    echo -e "🔹${FORMATTED_TOKENS}\n------------------------------------------"
done

# 🔹 Vérification des résultats avec diff
echo -e "${BLUE}🔍 Vérification des résultats...${NC}"
diff -u "$EXPECTED_FILE" "$ACTUAL_FILE" > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Tous les tests sont PASSÉS avec succès !${NC}"
else
    echo -e "${RED}❌ Certains tests ont ÉCHOUÉ. Vérifie '$ACTUAL_FILE'.${NC}"
fi

echo -e "${GREEN}✅ All tests completed!${NC}"
