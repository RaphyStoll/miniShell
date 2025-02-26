#include "../header/libft_bonus.h"

// Fonction pour exécuter les tests de `ft_lstnew`
void test_lstnew(void *content, int test_num, const char *test_name, int *passed_tests)
{
    t_list *node = ft_lstnew(content);
    if (node && node->content == content && node->next == NULL)
    {
        // Test passed
    }
    else
    {
        printf("Test %d (%s) failed ❌\n", test_num, test_name);
        *passed_tests = 0;
    }
    free(node);
}

int main(void)
{
    int passed_tests = 1;

    int value1 = 42;
    int value2 = -42;
    int value3 = 0;
    char *str1 = "Hello, world!";
    char *str2 = "";
    char str3[] = "Another test string";
    double value4 = 3.14;
    float value5 = -2.71;
    char value6 = 'a';
    void *ptr = NULL;

    // Déclaration des tests et leurs résultats attendus
    test_lstnew(&value1, 1, "Integer value 1", &passed_tests);
    test_lstnew(&value2, 2, "Integer value 2", &passed_tests);
    test_lstnew(&value3, 3, "Integer value 3", &passed_tests);
    test_lstnew(str1, 4, "String value 1", &passed_tests);
    test_lstnew(str2, 5, "String value 2", &passed_tests);
    test_lstnew(str3, 6, "String value 3", &passed_tests);
    test_lstnew(&value4, 7, "Double value", &passed_tests);
    test_lstnew(&value5, 8, "Float value", &passed_tests);
    test_lstnew(&value6, 9, "Char value", &passed_tests);
    test_lstnew(ptr, 10, "Null pointer", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_lstnew ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstnew ❌\n");
    }

    return 0;
}