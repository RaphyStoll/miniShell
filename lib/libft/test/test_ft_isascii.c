#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_isascii`
void test_isascii(int c, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_isascii(c);
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
    test_isascii('a', isascii('a'), 1, "Lowercase alphabet", &passed_tests);
    test_isascii('Z', isascii('Z'), 2, "Uppercase alphabet", &passed_tests);
    test_isascii('0', isascii('0'), 3, "Digit 0", &passed_tests);
    test_isascii('9', isascii('9'), 4, "Digit 9", &passed_tests);
    test_isascii('!', isascii('!'), 5, "Exclamation mark", &passed_tests);
    test_isascii(' ', isascii(' '), 6, "Space", &passed_tests);
    test_isascii('\n', isascii('\n'), 7, "Newline", &passed_tests);
    test_isascii(128, isascii(128), 8, "Out of ASCII range", &passed_tests);
    test_isascii(0, isascii(0), 9, "Null character", &passed_tests);
    test_isascii(127, isascii(127), 10, "DEL character", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_isascii ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_isascii ❌\n");
    }

    return 0;
}