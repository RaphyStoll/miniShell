#include "../header/libft_bonus.h"

// Fonction pour transformer une chaîne en majuscule
void *to_upper(void *content)
{
    char *str = strdup((char *)content);
    if (!str)
        return NULL;

    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

// Fonction pour libérer la mémoire d'une chaîne
void del(void *content)
{
    free(content);
}

// Fonction pour créer un nouvel élément de liste
t_list *create_elem(char *content)
{
    char *content_copy = strdup(content);
    if (!content_copy)
        return NULL;
    t_list *elem = ft_lstnew(content_copy);
    return elem;
}

// Fonction pour exécuter les tests de `ft_lstmap`
void test_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *), const char *expected[], int test_num, const char *test_name, int *passed_tests)
{
    t_list *new_lst = ft_lstmap(lst, f, del);

    int i = 0;
    t_list *current = new_lst;
    while (current)
    {
        if (strcmp(current->content, expected[i]) != 0)
        {
            // Test échoué
            printf("Test %d (%s) failed at element %d: expected '%s', got '%s' ❌\n", test_num, test_name, i, expected[i], (char *)current->content);
            *passed_tests = 0;
            break;
        }
        current = current->next;
        i++;
    }

    // Libérer la mémoire allouée pour la nouvelle liste
    current = new_lst;
    t_list *next;
    while (current)
    {
        next = current->next;
        del(current->content);
        free(current);
        current = next;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    t_list *lst1 = create_elem("hello");
    lst1->next = create_elem("world");
    lst1->next->next = create_elem("foo");
    lst1->next->next->next = create_elem("bar");

    const char *expected1[] = {"HELLO", "WORLD", "FOO", "BAR"};
    test_lstmap(lst1, to_upper, del, expected1, 1, "Convert all elements to uppercase", &passed_tests);

    // Libérer la mémoire allouée pour la liste initiale
    t_list *current = lst1;
    t_list *next;
    while (current)
    {
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_lstmap ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstmap ❌\n");
    }

    return 0;
}