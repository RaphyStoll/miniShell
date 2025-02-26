#include "../header/libft_bonus.h"

// Fonction pour transformer chaque élément de la liste en majuscule
void to_upper(void *content)
{
    char *str = (char *)content;
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
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

// Fonction pour exécuter les tests de `ft_lstiter`
void test_lstiter(t_list *lst, void (*f)(void *), const char *expected[], int test_num, const char *test_name, int *passed_tests)
{
    ft_lstiter(lst, f);

    int i = 0;
    t_list *current = lst;
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
    test_lstiter(lst1, to_upper, expected1, 1, "Convert all elements to uppercase", &passed_tests);

    // Libérer la mémoire allouée
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
        printf("All tests passed for ft_lstiter ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_lstiter ❌\n");
    }

    return 0;
}