#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strtrim`
void test_strtrim(const char *s1, const char *set, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_strtrim(s1, set);

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
    test_strtrim("  Hello, world!  ", " ", "Hello, world!", 1, "Trim spaces", &passed_tests);
    test_strtrim("xxHello, world!xx", "x", "Hello, world!", 2, "Trim 'x'", &passed_tests);
    test_strtrim("xxHello, world!", "x", "Hello, world!", 3, "Trim 'x' from start", &passed_tests);
    test_strtrim("Hello, world!xx", "x", "Hello, world!", 4, "Trim 'x' from end", &passed_tests);
    test_strtrim("  xxHello, world!xx  ", " x", "Hello, world!", 5, "Trim ' ' and 'x'", &passed_tests);
    test_strtrim("Hello, world!", " ", "Hello, world!", 6, "Trim nothing", &passed_tests);
    test_strtrim("Hello, world!", "", "Hello, world!", 7, "Trim empty set", &passed_tests);
    test_strtrim("aaaHello, world!aaa", "a", "Hello, world!", 8, "Trim 'a'", &passed_tests);
    test_strtrim("", " ", "", 9, "Trim empty string", &passed_tests);
    test_strtrim("   ", " ", "", 10, "Trim spaces only", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strtrim ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strtrim ❌\n");
    }

    return 0;
}