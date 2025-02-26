#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_isalnum`
void test_isalnum(int c, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_isalnum(c);
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
    test_isalnum('a', isalnum('a'), 1, "Lowercase alphabet", &passed_tests);
    test_isalnum('Z', isalnum('Z'), 2, "Uppercase alphabet", &passed_tests);
    test_isalnum('0', isalnum('0'), 3, "Digit 0", &passed_tests);
    test_isalnum('9', isalnum('9'), 4, "Digit 9", &passed_tests);
    test_isalnum('!', isalnum('!'), 5, "Exclamation mark", &passed_tests);
    test_isalnum(' ', isalnum(' '), 6, "Space", &passed_tests);
    test_isalnum('\n', isalnum('\n'), 7, "Newline", &passed_tests);
    test_isalnum('1', isalnum('1'), 8, "Digit 1", &passed_tests);
    test_isalnum('m', isalnum('m'), 9, "Lowercase m", &passed_tests);
    test_isalnum('%', isalnum('%'), 10, "Percent sign", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_isalnum ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_isalnum ❌\n");
    }

    return 0;
}