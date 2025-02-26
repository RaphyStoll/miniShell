#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strrchr`
void test_strrchr(const char *s, int c, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_strrchr(s, c);

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
    test_strrchr(str1, 'o', str1 + 8, 1, "Find last 'o' in string", &passed_tests);
    test_strrchr(str1, 'z', NULL, 2, "Find 'z' in string (not present)", &passed_tests);
    test_strrchr(str1, 'H', str1, 3, "Find 'H' in string", &passed_tests);
    test_strrchr(str1, ',', str1 + 5, 4, "Find ',' in string", &passed_tests);
    test_strrchr(str1, '!', str1 + 12, 5, "Find '!' in string", &passed_tests);
    test_strrchr(str1, '\0', str1 + 13, 6, "Find null terminator", &passed_tests);
    test_strrchr("", '\0', "", 7, "Find null terminator in empty string", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strrchr ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strrchr ❌\n");
    }

    return 0;
}