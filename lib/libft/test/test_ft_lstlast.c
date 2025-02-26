#include "../header/libft_bonus.h"

// Fonction pour exécuter les tests de `ft_lstlast`
void test_lstlast(t_list *lst, t_list *expected_last, int test_num, const char *test_name, int *passed_tests)
{
    t_list *last = ft_lstlast(lst);
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

    // Créer des listes pour les tests
    t_list *lst1 = ft_lstnew("First");
    t_list *expected_last1 = lst1;

    t_list *lst2 = ft_lstnew("First");
    t_list *second2 = ft_lstnew("Second");
    t_list *expected_last2 = second2;
    lst2->next = second2;

    t_list *lst3 = ft_lstnew("First");
    t_list *second3 = ft_lstnew("Second");
    t_list *third3 = ft_lstnew("Third");
    t_list *expected_last3 = third3;
    lst3->next = second3;
    second3->next = third3;

    t_list *lst4 = NULL;
    t_list *expected_last4 = NULL;

    // Déclaration des tests et leurs résultats attendus
    test_lstlast(lst1, expected_last1, 1, "Single element list", &passed_tests);
    test_lstlast(lst2, expected_last2, 2, "Two element list", &passed_tests);
    test_lstlast(lst3, expected_last3, 3, "Three element list", &passed_tests);
    test_lstlast(lst4, expected_last4, 4, "Empty list", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_lstlast ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstlast ❌\n");
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
    while (lst3)
    {
        current = lst3->next;
        free(lst3);
        lst3 = current;
    }

    return 0;
}