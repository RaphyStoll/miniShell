#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strjoin`
void test_strjoin(const char *s1, const char *s2, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_strjoin(s1, s2);

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
    test_strjoin("Hello, ", "world!", "Hello, world!", 1, "Join 'Hello, ' and 'world!'", &passed_tests);
    test_strjoin("", "world!", "world!", 2, "Join empty string and 'world!'", &passed_tests);
    test_strjoin("Hello, ", "", "Hello, ", 3, "Join 'Hello, ' and empty string", &passed_tests);
    test_strjoin("", "", "", 4, "Join two empty strings", &passed_tests);
    test_strjoin("foo", "bar", "foobar", 5, "Join 'foo' and 'bar'", &passed_tests);
    test_strjoin("123", "456", "123456", 6, "Join '123' and '456'", &passed_tests);
    test_strjoin("42", " 42", "42 42", 7, "Join '42' and ' 42'", &passed_tests);
    test_strjoin("!@#$%^", "&*()", "!@#$%^&*()", 8, "Join special characters", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strjoin ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strjoin ❌\n");
    }

    return 0;
}