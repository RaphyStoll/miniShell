#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strlcpy`
void test_strlcpy(char *dst, const char *src, size_t dstsize, size_t expected, const char *expected_str, int test_num, const char *test_name, int *passed_tests)
{
    size_t result = ft_strlcpy(dst, src, dstsize);

    if (result != expected || strcmp(dst, expected_str) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected '%s' (len: %zu), got '%s' (len: %zu) ❌\n", test_num, test_name, expected_str, expected, dst, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;
    char buffer[50];

    // Réinitialisation du buffer pour chaque test
    strcpy(buffer, "Initial");
    test_strlcpy(buffer, "Hello, world!", 50, strlen("Hello, world!"), "Hello, world!", 1, "Copy within buffer size", &passed_tests);

    strcpy(buffer, "Initial");
    test_strlcpy(buffer, "Hello, world!", 0, strlen("Hello, world!"), "Initial", 2, "Zero buffer size", &passed_tests);

    strcpy(buffer, "Initial");
    test_strlcpy(buffer, "Hello, world!", 5, strlen("Hello, world!"), "Hell", 3, "Buffer size smaller than source length", &passed_tests);

    strcpy(buffer, "");
    test_strlcpy(buffer, "Hello", 50, strlen("Hello"), "Hello", 4, "Copy into empty buffer", &passed_tests);

    strcpy(buffer, "Initial");
    test_strlcpy(buffer, "", 50, 0, "", 5, "Copy empty string", &passed_tests);

    strcpy(buffer, "Initial");
    test_strlcpy(buffer, "Hello", 6, strlen("Hello"), "Hello", 6, "Copy with exact buffer size", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strlcpy ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strlcpy ❌\n");
    }

    return 0;
}