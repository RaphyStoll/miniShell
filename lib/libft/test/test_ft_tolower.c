#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_tolower`
void test_tolower(int c, int expected, int test_num, const char *test_name, int *passed_tests)
{
    int result = ft_tolower(c);

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
    test_tolower('A', 'a', 1, "Convert 'A' to 'a'", &passed_tests);
    test_tolower('Z', 'z', 2, "Convert 'Z' to 'z'", &passed_tests);
    test_tolower('a', 'a', 3, "Convert 'a' to 'a'", &passed_tests);
    test_tolower('z', 'z', 4, "Convert 'z' to 'z'", &passed_tests);
    test_tolower('0', '0', 5, "Convert '0' to '0'", &passed_tests);
    test_tolower('9', '9', 6, "Convert '9' to '9'", &passed_tests);
    test_tolower('!', '!', 7, "Convert '!' to '!'", &passed_tests);
    test_tolower(' ', ' ', 8, "Convert ' ' to ' '", &passed_tests);
    test_tolower('@', '@', 9, "Convert '@' to '@'", &passed_tests);
    test_tolower('[', '[', 10, "Convert '[' to '['", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_tolower ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_tolower ❌\n");
    }

    return 0;
}