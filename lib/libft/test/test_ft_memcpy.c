#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_memcpy`
void test_memcpy(void *dest, const void *src, size_t n, const void *expected, int test_num, const char *test_name, int *passed_tests)
{
    ft_memcpy(dest, src, n);

    if (memcmp(dest, expected, n) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected '%s', got '%s' ❌\n", test_num, test_name, (char *)expected, (char *)dest);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    char dest1[50] = "Hello, world!";
    char src1[50] = "Goodbye!";
    test_memcpy(dest1, src1, 8, "Goodbye!", 1, "Basic copy", &passed_tests);

    char dest2[50] = "Hello, world!";
    char src2[50] = "Hello, world!";
    test_memcpy(dest2 + 2, src2, 6, "Hello, world!", 2, "Overlapping copy forward", &passed_tests);

    char dest3[50] = "Hello, world!";
    test_memcpy(dest3, dest3 + 2, 6, "llo, world!", 3, "Overlapping copy backward", &passed_tests);

    char dest4[50] = "Hello, world!";
    char src4[50] = "";
    test_memcpy(dest4, src4, 0, "Hello, world!", 4, "Zero length copy", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_memcpy ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_memcpy ❌\n");
    }

    return 0;
}