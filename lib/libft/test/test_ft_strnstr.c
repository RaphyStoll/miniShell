#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strnstr`
void test_strnstr(const char *haystack, const char *needle, size_t len, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_strnstr(haystack, needle, len);

    if (result != expected)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected \"%s\", got \"%s\" ❌\n", test_num, test_name, expected ? expected : "NULL", result ? result : "NULL");
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    char haystack1[] = "Hello, world!";
    test_strnstr(haystack1, "world", 13, haystack1 + 7, 1, "Find 'world' in 'Hello, world!'", &passed_tests);
    test_strnstr(haystack1, "world", 5, NULL, 2, "Find 'world' in first 5 characters", &passed_tests);
    test_strnstr(haystack1, "", 13, haystack1, 3, "Find empty string in 'Hello, world!'", &passed_tests);
    test_strnstr(haystack1, "Hello", 13, haystack1, 4, "Find 'Hello' in 'Hello, world!'", &passed_tests);
    test_strnstr(haystack1, "world!", 12, NULL, 5, "Find 'world!' with insufficient length", &passed_tests);
    test_strnstr(haystack1, "!", 13, haystack1 + 12, 6, "Find '!' in 'Hello, world!'", &passed_tests);
    test_strnstr(haystack1, "Hello, world!", 13, haystack1, 7, "Find full string in itself", &passed_tests);
    test_strnstr(haystack1, "Hello, world!!!", 13, NULL, 8, "Find longer string than haystack", &passed_tests);
    test_strnstr("", "Hello", 5, NULL, 9, "Find 'Hello' in empty string", &passed_tests);
    
    char haystack2[] = "12345";
    test_strnstr(haystack2, "34", 5, haystack2 + 2, 10, "Find '34' in '12345'", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strnstr ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strnstr ❌\n");
    }

    return 0;
}