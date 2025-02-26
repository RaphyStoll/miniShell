#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strchr`
void test_strchr(const char *s, int c, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_strchr(s, c);

    if (result != expected)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected '%s', got '%s' ❌\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    char str1[] = "Hello, world!";
    test_strchr(str1, 'w', str1 + 7, 1, "Find 'w' in string", &passed_tests);
    test_strchr(str1, 'z', NULL, 2, "Find 'z' in string (not present)", &passed_tests);
    test_strchr(str1, 'H', str1, 3, "Find 'H' in string", &passed_tests);
    test_strchr(str1, ',', str1 + 5, 4, "Find ',' in string", &passed_tests);
    test_strchr(str1, 'o', str1 + 4, 5, "Find first 'o' in string", &passed_tests);
    test_strchr(str1, '!', str1 + 12, 6, "Find '!' in string", &passed_tests);
    test_strchr(str1, '\0', str1 + 13, 7, "Find null terminator", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strchr ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strchr ❌\n");
    }

    return 0;
}