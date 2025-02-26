#include "../header/libft_bonus.h"

// Fonction de suppression pour `ft_lstclear`
void del(void *content)
{
    (void)content;  // Supprime le warning de variable non utilisée
}

// Fonction pour exécuter les tests de `ft_lstclear`
void test_lstclear(t_list **lst, int test_num, const char *test_name, int *passed_tests)
{
    ft_lstclear(lst, del);
    if (*lst != NULL)
    {
        // Test échoué
        printf("Test %d (%s) failed: list is not NULL after clear ❌\n", test_num, test_name);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Créer des listes pour les tests
    t_list *lst1 = ft_lstnew("Node 1");
    t_list *second1 = ft_lstnew("Node 2");
    lst1->next = second1;

    t_list *lst2 = ft_lstnew("Node 1");

    t_list *lst3 = NULL;

    // Déclaration des tests et leurs résultats attendus
    test_lstclear(&lst1, 1, "Clear two-element list", &passed_tests);
    test_lstclear(&lst2, 2, "Clear single-element list", &passed_tests);
    test_lstclear(&lst3, 3, "Clear NULL list", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_lstclear ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstclear ❌\n");
    }

    return 0;
}