#!/bin/bash

# Chemin de l'exécutable
EXEC="./test_lexing"

# Vérification de l'existence de l'exécutable
if [ ! -x "$EXEC" ]; then
    echo "🔴 Erreur : L'exécutable $EXEC n'existe pas."
    exit 1
fi

# Liste des tests
declare -a TESTS=(
    "echo Hello, world!"
    "ls -l | grep .c"
    "echo 'hello world' > file.txt"
    "cat << EOF"
    "&& || | < > >> <<"
    "'unterminated quote"
    "echo Hello && ls -l || pwd"
    "(echo test)"
    "(echo test"
    "echo \"Hello \$(ls -l)\""
)

echo "======================="
echo "   TEST LEXER SCRIPT   "
echo "======================="
echo ""

for test in "${TESTS[@]}"; do
    echo "➜ Test: $test"
    echo "$test" | "$EXEC"
    echo "-----------------------"
done

echo "✅ Tests terminés."