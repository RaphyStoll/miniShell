#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strlen`
void test_strlen(const char *s, size_t expected, int test_num, const char *test_name, int *passed_tests)
{
    size_t result = ft_strlen(s);

    if (result != expected)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected length %zu, got %zu ❌\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    test_strlen("Hello, world!", strlen("Hello, world!"), 1, "Length of 'Hello, world!'", &passed_tests);
    test_strlen("", 0, 2, "Length of empty string", &passed_tests);
    test_strlen("42", strlen("42"), 3, "Length of '42'", &passed_tests);
    test_strlen("!@#$%^&*()", strlen("!@#$%^&*()"), 4, "Length of special characters", &passed_tests);
    test_strlen("This is a longer test string.", strlen("This is a longer test string."), 5, "Length of longer string", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strlen ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strlen ❌\n");
    }

    return 0;
}