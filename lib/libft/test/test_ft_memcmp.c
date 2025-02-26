#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_memcmp`
void test_memcmp(const void *s1, const void *s2, size_t n, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_memcmp(s1, s2, n);
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
    char str1[] = "abcdef";
    char str2[] = "abcdeg";
    char str3[] = "abcdef";
    char str4[] = "abcdEf";
    char str5[] = "";

    test_memcmp(str1, str2, 6, -1, 1, "Compare different strings", &passed_tests);
    test_memcmp(str1, str3, 6, 0, 2, "Compare identical strings", &passed_tests);
    test_memcmp(str1, str4, 6, 1, 3, "Compare strings with different case", &passed_tests);
    test_memcmp(str1, str5, 6, 1, 4, "Compare string with empty string", &passed_tests);
    test_memcmp(str1, str2, 3, 0, 5, "Compare first 3 characters of different strings", &passed_tests);
    test_memcmp(str1, str2, 0, 0, 6, "Compare with zero length", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_memcmp ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_memcmp ❌\n");
    }

    return 0;
}