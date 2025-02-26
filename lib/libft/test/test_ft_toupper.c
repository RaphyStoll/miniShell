#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_toupper`
void test_toupper(int c, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_toupper(c);

    if (result != expected)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected '%c' (%d), got '%c' (%d) ❌\n", test_num, test_name, expected, expected, result, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    test_toupper('a', 'A', 1, "Convert 'a' to 'A'", &passed_tests);
    test_toupper('z', 'Z', 2, "Convert 'z' to 'Z'", &passed_tests);
    test_toupper('A', 'A', 3, "Convert 'A' to 'A'", &passed_tests);
    test_toupper('Z', 'Z', 4, "Convert 'Z' to 'Z'", &passed_tests);
    test_toupper('0', '0', 5, "Convert '0' to '0'", &passed_tests);
    test_toupper('9', '9', 6, "Convert '9' to '9'", &passed_tests);
    test_toupper('!', '!', 7, "Convert '!' to '!'", &passed_tests);
    test_toupper(' ', ' ', 8, "Convert ' ' to ' '", &passed_tests);
    test_toupper('@', '@', 9, "Convert '@' to '@'", &passed_tests);
    test_toupper('[', '[', 10, "Convert '[' to '['", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_toupper ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_toupper ❌\n");
    }

    return 0;
}