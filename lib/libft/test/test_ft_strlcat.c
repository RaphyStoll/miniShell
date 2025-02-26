#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_strlcat`
void test_strlcat(char *dst, const char *src, size_t dstsize, size_t expected_len, const char *expected_str, int test_num, const char *test_name, int *passed_tests)
{
    size_t result = ft_strlcat(dst, src, dstsize);

    if (result != expected_len || strcmp(dst, expected_str) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected '%s' (len: %zu), got '%s' (len: %zu) ❌\n", test_num, test_name, expected_str, expected_len, dst, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;
    char buffer[50];

    // Réinitialisation du buffer pour chaque test
    strcpy(buffer, "Hello");
    test_strlcat(buffer, ", world!", 50, strlen("Hello, world!"), "Hello, world!", 1, "Concatenate within buffer size", &passed_tests);

    strcpy(buffer, "Hello");
    test_strlcat(buffer, ", world!", 0, strlen("Hello") + strlen(", world!"), "Hello", 2, "Zero buffer size", &passed_tests);

    strcpy(buffer, "Hello");
    test_strlcat(buffer, ", world!", 5, strlen("Hello") + strlen(", world!"), "Hello", 3, "Buffer size smaller than destination length", &passed_tests);

    strcpy(buffer, "Hello");
    test_strlcat(buffer, ", world!", 10, strlen("Hello") + strlen(", world!"), "Hello, wo", 4, "Buffer size smaller than result length", &passed_tests);

    strcpy(buffer, "");
    test_strlcat(buffer, "Hello", 50, strlen("Hello"), "Hello", 5, "Concatenate into empty buffer", &passed_tests);

    strcpy(buffer, "Hello");
    test_strlcat(buffer, "", 50, strlen("Hello"), "Hello", 6, "Concatenate empty string", &passed_tests);

    strcpy(buffer, "Hello");
    test_strlcat(buffer, " world!", 13, strlen("Hello") + strlen(" world!"), "Hello world!", 7, "Concatenate with exact buffer size", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_strlcat ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_strlcat ❌\n");
    }

    return 0;
}