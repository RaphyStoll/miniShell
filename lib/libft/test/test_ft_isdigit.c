#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_isdigit`
void test_isdigit(int c, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_isdigit(c);
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
    test_isdigit('0', isdigit('0'), 1, "Digit 0", &passed_tests);
    test_isdigit('9', isdigit('9'), 2, "Digit 9", &passed_tests);
    test_isdigit('5', isdigit('5'), 3, "Digit 5", &passed_tests);
    test_isdigit('a', isdigit('a'), 4, "Lowercase letter", &passed_tests);
    test_isdigit('Z', isdigit('Z'), 5, "Uppercase letter", &passed_tests);
    test_isdigit('!', isdigit('!'), 6, "Exclamation mark", &passed_tests);
    test_isdigit(' ', isdigit(' '), 7, "Space", &passed_tests);
    test_isdigit('\n', isdigit('\n'), 8, "Newline", &passed_tests);
    test_isdigit('3', isdigit('3'), 9, "Digit 3", &passed_tests);
    test_isdigit('%', isdigit('%'), 10, "Percent sign", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_isdigit ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_isdigit ❌\n");
    }

    return 0;
}