#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_isprint`
void test_isprint(int c, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_isprint(c);
    if (result != expected)
    {
        // Test échoué
        printf("Test %d (%s) failed: attendu %d, obtenu %d ❌\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    test_isprint(' ', isprint(' '), 1, "Space", &passed_tests);
    test_isprint('~', isprint('~'), 2, "Tilde", &passed_tests);
    test_isprint('a', isprint('a'), 3, "Lowercase letter", &passed_tests);
    test_isprint('Z', isprint('Z'), 4, "Uppercase letter", &passed_tests);
    test_isprint('0', isprint('0'), 5, "Digit 0", &passed_tests);
    test_isprint('9', isprint('9'), 6, "Digit 9", &passed_tests);
    test_isprint('!', isprint('!'), 7, "Exclamation mark", &passed_tests);
    test_isprint('\n', isprint('\n'), 8, "Newline", &passed_tests);
    test_isprint(127, isprint(127), 9, "DEL character", &passed_tests);
    test_isprint('%', isprint('%'), 10, "Percent sign", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_isprint ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_isprint ❌\n");
    }

    return 0;
}