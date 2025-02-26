#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strdup`
void test_strdup(const char *s, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_strdup(s);

    if (result == NULL || strcmp(result, expected) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected '%s', got '%s' ❌\n", test_num, test_name, expected, result ? result : "NULL");
        *passed_tests = 0;
    }

    free(result);
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    test_strdup("Hello, world!", "Hello, world!", 1, "Duplicate 'Hello, world!'", &passed_tests);
    test_strdup("", "", 2, "Duplicate empty string", &passed_tests);
    test_strdup("42", "42", 3, "Duplicate '42'", &passed_tests);
    test_strdup("!@#$%^&*()", "!@#$%^&*()", 4, "Duplicate special characters", &passed_tests);
    test_strdup("This is a longer test string.", "This is a longer test string.", 5, "Duplicate longer string", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strdup ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strdup ❌\n");
    }

    return 0;
}