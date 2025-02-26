#include "../header/libft.h"

// Fonction pour afficher les valeurs hexadécimales d'un buffer
void print_hex(const void *buffer, size_t length)
{
    const unsigned char *buf = (const unsigned char *)buffer;
    for (size_t i = 0; i < length; i++)
    {
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

// Fonction pour exécuter les tests de `ft_memset`
void test_memset(void *s, int c, size_t n, const void *expected, int test_num, const char *test_name, int *passed_tests)
{
    ft_memset(s, c, n);

    if (memcmp(s, expected, n) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed ❌\n", test_num, test_name);
        printf("Expected: ");
        print_hex(expected, n);
        printf("Got:      ");
        print_hex(s, n);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests et leurs résultats attendus
    char dest1[50] = "Hello, world!";
    char expected1[50] = "***** world!";
    test_memset(dest1, '*', 5, expected1, 1, "Basic memset", &passed_tests);

    char dest2[50] = "Hello, world!";
    char expected2[50] = "Hello, *****";
    test_memset(dest2 + 7, '*', 5, expected2 + 7, 2, "Offset memset", &passed_tests);

    char dest3[50] = "Hello, world!";
    char expected3[50] = "Hello, world!";
    test_memset(dest3, '*', 0, expected3, 3, "Zero length memset", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_memset ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_memset ❌\n");
    }

    return 0;
}