#include "../header/libft.h"


// Fonction pour exécuter les tests de `ft_atoi`
void test_atoi(const char *str, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_atoi(str);
    if (result != expected)
    {
        // Test échoué
        printf("Test %d (%s) failed: attendu %d, obtenu %d ❌\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    test_atoi("0", 0, 1, "Zero", &passed_tests);
    test_atoi("123", 123, 2, "Positive number", &passed_tests);
    test_atoi("-123", -123, 3, "Negative number", &passed_tests);
    test_atoi("2147483647", 2147483647, 4, "Max int", &passed_tests);
    test_atoi("-2147483648", -2147483648, 5, "Min int", &passed_tests);
    test_atoi("   42", 42, 6, "Positive number with leading spaces", &passed_tests);
    test_atoi("   -42", -42, 7, "Negative number with leading spaces", &passed_tests);
    test_atoi("+42", 42, 8, "Positive number with plus sign", &passed_tests);
    test_atoi("42abc", 42, 9, "Number with trailing characters", &passed_tests);
    test_atoi("-42abc", -42, 10, "Negative number with trailing characters", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_atoi ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_atoi ❌\n");
    }

    return 0;
}