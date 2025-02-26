#include "../header/libft_bonus.h"

// Fonction pour exécuter les tests de `ft_lstsize`
void test_lstsize(t_list *lst, int expected_size, int test_num, const char *test_name, int *passed_tests)
{
    int size = ft_lstsize(lst);
    if (size != expected_size)
    {
        // Test échoué
        printf("Test %d (%s) failed: attendu %d, obtenu %d ❌\n", test_num, test_name, expected_size, size);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");
    t_list *node4 = ft_lstnew("Node 4");
    t_list *node5 = ft_lstnew("Node 5");

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    // Déclaration des tests et leurs résultats attendus
    test_lstsize(NULL, 0, 1, "Empty list", &passed_tests);
    test_lstsize(node1, 5, 2, "List with 5 elements", &passed_tests);
    test_lstsize(node2, 4, 3, "List starting from second element", &passed_tests);
    test_lstsize(node3, 3, 4, "List starting from third element", &passed_tests);
    test_lstsize(node4, 2, 5, "List starting from fourth element", &passed_tests);
    test_lstsize(node5, 1, 6, "List starting from fifth element", &passed_tests);

    t_list *single_node = ft_lstnew("Single Node");
    test_lstsize(single_node, 1, 7, "Single element list", &passed_tests);

    t_list *head = NULL;
    test_lstsize(head, 0, 8, "Another empty list", &passed_tests);

    t_list *node6 = ft_lstnew("Node 6");
    t_list *node7 = ft_lstnew("Node 7");
    node6->next = node7;
    test_lstsize(node6, 2, 9, "List with 2 elements", &passed_tests);

    t_list *node8 = ft_lstnew("Node 8");
    test_lstsize(node8, 1, 10, "Another single element list", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_lstsize ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstsize ❌\n");
    }

    // Clean up allocated memory
    t_list *current = node1;
    t_list *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(single_node);
    free(node6);
    free(node7);
    free(node8);

    return 0;
}