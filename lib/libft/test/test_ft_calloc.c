#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_calloc`
void test_calloc(size_t count, size_t size, int test_num, const char *test_name, int *passed_tests)
{
    void *result = ft_calloc(count, size);
    if (!result)
    {
        printf("Test %d (%s) failed: allocation failed ❌\n", test_num, test_name);
        *passed_tests = 0;
        return;
    }

    void *expected = calloc(count, size);
    if (!expected)
    {
        printf("Test %d (%s) failed: system calloc failed ❌\n", test_num, test_name);
        free(result);
        *passed_tests = 0;
        return;
    }

    if (memcmp(result, expected, count * size) != 0)
    {
        printf("Test %d (%s) failed ❌\n", test_num, test_name);
        *passed_tests = 0;
    }

    free(result);
    free(expected);
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    test_calloc(5, sizeof(int), 1, "Allocate array of 5 integers", &passed_tests);
    test_calloc(10, sizeof(char), 2, "Allocate array of 10 characters", &passed_tests);
    test_calloc(0, sizeof(int), 3, "Allocate zero elements", &passed_tests);
    test_calloc(1, sizeof(double), 4, "Allocate one double", &passed_tests);
    test_calloc(100, sizeof(float), 5, "Allocate array of 100 floats", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_calloc ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_calloc ❌\n");
    }

    return 0;
}