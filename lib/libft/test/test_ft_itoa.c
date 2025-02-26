#include "../header/libft.h"

// * Fonction pour exécuter les tests de `ft_itoa`
void test_itoa(int n, const char *expected, int test_num, const char *test_name, int *passed_tests)
{
    char *result = ft_itoa(n);
    if (strcmp(result, expected) != 0)
    {
        // ! Test échoué
        printf("Test %d (%s) failed: attendu '%s', obtenu '%s'\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
    free(result);
}

int main(void)
{
    int passed_tests = 1;

    // * Déclaration des tests et leurs résultats attendus
    test_itoa(0, "0", 1, "Zero", &passed_tests);
    test_itoa(123, "123", 2, "Positive number", &passed_tests);
	test_itoa(2147483647, "2147483647", 4, "Max int", &passed_tests);
    test_itoa(-2147483648, "-2147483648", 5, "Min int", &passed_tests);
    test_itoa(42, "42", 6, "Positive number", &passed_tests);
    test_itoa(-42, "-42", 7, "Negative number", &passed_tests);
    test_itoa(1, "1", 8, "Small positive number", &passed_tests);
    test_itoa(-1, "-1", 9, "Small negative number", &passed_tests);
    test_itoa(1000000, "1000000", 10, "Large positive number", &passed_tests);

    // * Afficher le résultat global des tests
    if (passed_tests)
    {
        // ! Tous les tests sont passés
        printf("All tests passed for ft_itoa ✅\n");
    }
    else
    {
        // ! Certains tests ont échoué
        printf("Some tests failed for ft_itoa ❌\n");
    }

    return 0;
}