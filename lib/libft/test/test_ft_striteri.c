#include "../header/libft.h"

// Fonction de transformation pour les tests
void test_transform(unsigned int i, char *c)
{
    if (i % 2 == 0)
        *c = (*c >= 'a' && *c <= 'z') ? *c - 'a' + 'A' : *c;
    else
        *c = (*c >= 'A' && *c <= 'Z') ? *c - 'A' + 'a' : *c;
}

// Fonction de test
void test_striteri(char *input, char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *s = strdup(input);
    ft_striteri(s, test_transform);
    if (strcmp(s, expected) != 0)
    {
        printf("Test %d (%s) failed: expected \"%s\", got \"%s\" ❌\n", test_num, test_name, expected, s);
        *passed_tests = 0;
    }
    free(s);
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    test_striteri("abcde", "AbCdE", 1, "test1", &passed_tests);
    test_striteri("ABCDE", "AbCdE", 2, "test2", &passed_tests);
    test_striteri("12345", "12345", 3, "test3", &passed_tests);
    test_striteri("a1b2c3", "A1B2C3", 4, "test4", &passed_tests);
    test_striteri("", "", 5, "test5", &passed_tests);
    test_striteri("a", "A", 6, "test6", &passed_tests);
    test_striteri("Z", "Z", 7, "test7", &passed_tests);
    test_striteri("Hello World!", "HeLlO WoRlD!", 8, "test8", &passed_tests);
    test_striteri("HeLlO WoRlD!", "HeLlO WoRlD!", 9, "test9", &passed_tests);
    test_striteri("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "AbCdEfGhIjKlMnOpQrStUvWxYz", 10, "test10", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_striteri ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_striteri ❌\n");
    }

    return 0;
}