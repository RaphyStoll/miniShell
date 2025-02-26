#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_substr`
void test_substr(const char *s, unsigned int start, size_t len, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_substr(s, start, len);

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
    test_substr("Hello, world!", 7, 5, "world", 1, "Extract 'world' from 'Hello, world!'", &passed_tests);
    test_substr("Hello, world!", 0, 5, "Hello", 2, "Extract 'Hello' from 'Hello, world!'", &passed_tests);
    test_substr("Hello, world!", 7, 20, "world!", 3, "Extract 'world!' with len exceeding string length", &passed_tests);
    test_substr("Hello, world!", 13, 5, "", 4, "Extract starting at string end", &passed_tests);
    test_substr("Hello, world!", 14, 5, "", 5, "Extract starting beyond string end", &passed_tests);
    test_substr("Hello, world!", 7, 0, "", 6, "Extract with zero length", &passed_tests);
    test_substr("", 0, 5, "", 7, "Extract from empty string", &passed_tests);
    test_substr("Hello", 1, 10, "ello", 8, "Extract with len exceeding remaining string", &passed_tests);
    test_substr("abcdef", 2, 3, "cde", 9, "Extract 'cde' from 'abcdef'", &passed_tests);
    test_substr("42", 1, 1, "2", 10, "Extract single character from '42'", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_substr ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_substr ❌\n");
    }

    return 0;
}