#include "../header/libft_bonus.h"

// Fonction pour exécuter les tests de `ft_lstadd_back`
void test_lstadd_back(t_list **lst, t_list *new, t_list *expected_last, int test_num, const char *test_name, int *passed_tests)
{
    ft_lstadd_back(lst, new);
    t_list *last = *lst;

    // Aller au dernier élément de la liste
    while (last && last->next)
        last = last->next;

    if (last != expected_last)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected last node with content '%s', got '%s' ❌\n", test_num, test_name, (char *)expected_last->content, last ? (char *)last->content : "NULL");
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    t_list *lst1 = ft_lstnew("First");
    t_list *new1 = ft_lstnew("New Last");
    t_list *expected_last1 = new1;

    t_list *lst2 = ft_lstnew("First");
    t_list *second2 = ft_lstnew("Second");
    lst2->next = second2;
    t_list *new2 = ft_lstnew("New Last");
    t_list *expected_last2 = new2;

    // Déclaration des tests et leurs résultats attendus
    test_lstadd_back(&lst1, new1, expected_last1, 1, "Add to single element list", &passed_tests);
    test_lstadd_back(&lst2, new2, expected_last2, 2, "Add to two element list", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_lstadd_back ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstadd_back ❌\n");
    }

    // Clean up allocated memory
    t_list *current;
    while (lst1)
    {
        current = lst1->next;
        free(lst1);
        lst1 = current;
    }
    while (lst2)
    {
        current = lst2->next;
        free(lst2);
        lst2 = current;
    }

    return 0;
}