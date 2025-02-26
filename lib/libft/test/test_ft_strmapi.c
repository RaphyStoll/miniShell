#include "../header/libft.h"

// Fonction de transformation pour les tests
char test_transform(unsigned int i, char c)
{
    if (i % 2 == 0)
        return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
    else
        return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}

// Fonction pour exécuter les tests de `ft_strmapi`
void test_strmapi(const char *s, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_strmapi(s, test_transform);

    if (result == NULL || strcmp(result, expected) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected \"%s\", got \"%s\" ❌\n", test_num, test_name, expected, result ? result : "NULL");
        *passed_tests = 0;
    }

    free(result);
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    test_strmapi("abcde", "AbCdE", 1, "Transform 'abcde'", &passed_tests);
    test_strmapi("ABCDE", "AbCdE", 2, "Transform 'ABCDE'", &passed_tests);
    test_strmapi("12345", "12345", 3, "Transform '12345'", &passed_tests);
    test_strmapi("a1b2c3", "A1B2C3", 4, "Transform 'a1b2c3'", &passed_tests);
    test_strmapi("", "", 5, "Transform empty string", &passed_tests);
    test_strmapi("a", "A", 6, "Transform 'a'", &passed_tests);
    test_strmapi("Z", "Z", 7, "Transform 'Z'", &passed_tests);
    test_strmapi("Hello World!", "HeLlO WoRlD!", 8, "Transform 'Hello World!'", &passed_tests);
    test_strmapi("HeLlO WoRlD!", "HeLlO WoRlD!", 9, "Transform 'HeLlO WoRlD!'", &passed_tests);
    test_strmapi("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "AbCdEfGhIjKlMnOpQrStUvWxYz", 10, "Transform 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strmapi ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strmapi ❌\n");
    }

    return 0;
}