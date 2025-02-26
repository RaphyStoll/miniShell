#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_memchr`
void test_memchr(const void *s, int c, size_t n, const void *expected, int test_num, const char *test_name, int *passed_tests)
{
    void *result = ft_memchr(s, c, n);
    if (result != expected)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected %p, got %p ❌\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    char str1[] = "Hello, world!";
    test_memchr(str1, 'w', 13, str1 + 7, 1, "Find 'w' in string", &passed_tests);
    test_memchr(str1, 'z', 13, NULL, 2, "Find 'z' in string (not present)", &passed_tests);
    test_memchr(str1, 'H', 5, str1, 3, "Find 'H' in first 5 characters", &passed_tests);
    test_memchr(str1, ',', 13, str1 + 5, 4, "Find ',' in string", &passed_tests);
    test_memchr(str1, 'o', 5, str1 + 4, 5, "Find 'o' in first 4 characters", &passed_tests);
    test_memchr(str1, 'o', 13, str1 + 4, 6, "Find first 'o' in string", &passed_tests);
    test_memchr(str1, '!', 13, str1 + 12, 7, "Find '!' in string", &passed_tests);
    test_memchr(str1, 'H', 0, NULL, 8, "Find 'H' in first 0 characters", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_memchr ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_memchr ❌\n");
    }

    return 0;
}