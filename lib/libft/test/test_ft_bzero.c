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

// Fonction pour exécuter les tests de `ft_bzero`
void test_bzero(void *s, size_t n, void *expected, size_t len, int test_num, const char *test_name, int *passed_tests, int *failed_tests)
{
    ft_bzero(s, n);

    if (memcmp(s, expected, len) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed ❌\n", test_num, test_name);
        printf("Expected: ");
        print_hex(expected, len);
        printf("Got:      ");
        print_hex(s, len);
        *passed_tests = 0;
        (*failed_tests)++;
    }
}

int main(void)
{
    int passed_tests = 1;
    int failed_tests = 0;

    // Déclaration des tests et leurs résultats attendus
    char buffer1[10] = "123456789";
    char expected1[10] = "\0\0\0" "456789";  // Correct expected value for zeroing the first 3 bytes
    test_bzero(buffer1, 3, expected1, 10, 1, "Zero first 3 bytes", &passed_tests, &failed_tests);

    char buffer2[10] = "123456789";
    char expected2[10] = "123456" "\0\0\0";  // Correct expected value for zeroing the last 3 bytes
    test_bzero(buffer2 + 6, 3, expected2 + 6, 3, 2, "Zero last 3 bytes", &passed_tests, &failed_tests);

    char buffer3[10] = "123456789";
    char expected3[10] = "1" "\0\0" "456789";  // Correct expected value for zeroing the middle 2 bytes
    test_bzero(buffer3 + 1, 2, expected3 + 1, 2, 3, "Zero middle 2 bytes", &passed_tests, &failed_tests);

    char buffer4[10] = "123456789";
    char expected4[10] = "\0\0\0\0\0\0\0\0\0\0";  // Correct expected value for zeroing all bytes
    test_bzero(buffer4, 10, expected4, 10, 4, "Zero all bytes", &passed_tests, &failed_tests);

    char buffer5[10] = "123456789";
    char expected5[10] = "123456789";  // Correct expected value for zeroing 0 bytes
    test_bzero(buffer5, 0, expected5, 10, 5, "Zero 0 bytes", &passed_tests, &failed_tests);

    // Afficher le résultat global des tests
    if (passed_tests && failed_tests == 0)
    {
        printf("All tests passed for ft_bzero ✅\n");
    }
    else if (failed_tests > 0)
    {
        printf("Some tests failed for ft_bzero ❌\n");
    }

    return 0;
}