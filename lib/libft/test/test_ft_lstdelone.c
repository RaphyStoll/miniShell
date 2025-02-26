#include "../header/libft_bonus.h"

// Fonction de suppression pour `ft_lstdelone`
void del(void *content)
{
    (void)content;  // Supprime le warning de variable non utilisée
}

// Fonction pour exécuter les tests de `ft_lstdelone`
void test_lstdelone(t_list *node, int test_num, const char *test_name, int *passed_tests)
{
    if (node)
    {
        ft_lstdelone(node, del);
    }
    else
    {
        printf("Test %d (%s) failed: node is NULL before deletion ❌\n", test_num, test_name);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Créer des nœuds pour les tests
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew(NULL);

    // Déclaration des tests et leurs résultats attendus
    test_lstdelone(node1, 1, "Delete single node with content", &passed_tests);
    test_lstdelone(node2, 2, "Delete single node with different content", &passed_tests);
    test_lstdelone(node3, 3, "Delete single node with NULL content", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_lstdelone ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstdelone ❌\n");
    }

    return 0;
}