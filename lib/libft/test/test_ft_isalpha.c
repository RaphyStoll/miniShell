#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_isalpha`
void test_isalpha(int c, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_isalpha(c);
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
    test_isalpha('a', isalpha('a'), 1, "Lowercase alphabet", &passed_tests);
    test_isalpha('Z', isalpha('Z'), 2, "Uppercase alphabet", &passed_tests);
    test_isalpha('0', isalpha('0'), 3, "Digit 0", &passed_tests);
    test_isalpha('9', isalpha('9'), 4, "Digit 9", &passed_tests);
    test_isalpha('!', isalpha('!'), 5, "Exclamation mark", &passed_tests);
    test_isalpha(' ', isalpha(' '), 6, "Space", &passed_tests);
    test_isalpha('\n', isalpha('\n'), 7, "Newline", &passed_tests);
    test_isalpha('m', isalpha('m'), 8, "Lowercase m", &passed_tests);
    test_isalpha('%', isalpha('%'), 9, "Percent sign", &passed_tests);
    test_isalpha('G', isalpha('G'), 10, "Uppercase G", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_isalpha ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_isalpha ❌\n");
    }

    return 0;
}