#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strncmp`
void test_strncmp(const char *s1, const char *s2, size_t n, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_strncmp(s1, s2, n);

    if ((result == 0 && expected != 0) || (result != 0 && (expected == 0 || (result > 0 && expected < 0) || (result < 0 && expected > 0))))
    {
        // Test échoué
        printf("Test %d (%s) failed: expected %d, got %d ❌\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    test_strncmp("abcde", "abcde", 5, 0, 1, "Compare identical strings", &passed_tests);
    test_strncmp("abcde", "abcdf", 5, -1, 2, "Compare different strings", &passed_tests);
    test_strncmp("abcde", "abcdF", 5, 1, 3, "Compare case-sensitive strings", &passed_tests);
    test_strncmp("abc", "abcdef", 3, 0, 4, "Compare strings with common prefix", &passed_tests);
    test_strncmp("abc", "abcdef", 5, -1, 5, "Compare strings with common prefix and longer n", &passed_tests);
    test_strncmp("abcdef", "abc", 3, 0, 6, "Compare longer string with shorter string (n = 3)", &passed_tests);
    test_strncmp("abcdef", "abc", 6, 1, 7, "Compare longer string with shorter string (n = 6)", &passed_tests);
    test_strncmp("12345", "12345", 5, 0, 8, "Compare numeric strings", &passed_tests);
    test_strncmp("12345", "12346", 5, -1, 9, "Compare numeric strings with last digit different", &passed_tests);
    test_strncmp("", "", 1, 0, 10, "Compare empty strings", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strncmp ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strncmp ❌\n");
    }

    return 0;
}