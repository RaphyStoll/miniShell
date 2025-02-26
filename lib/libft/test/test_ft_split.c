#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_split`
void test_split(const char *s, char c, char **expected, int test_num, const char *test_name, int *passed_tests)
{
    char **result = ft_split(s, c);

    // Comparer chaque chaîne de caractères dans le tableau
    int i = 0;
    while (expected[i])
    {
        if (!result[i] || strcmp(result[i], expected[i]) != 0)
        {
            printf("Test %d (%s) failed: expected '%s', got '%s' ❌\n", test_num, test_name, expected[i], result[i] ? result[i] : "NULL");
            *passed_tests = 0;
            // Libérer la mémoire allouée
            i = 0;
            while (result[i])
            {
                free(result[i]);
                i++;
            }
            free(result);
            return;
        }
        i++;
    }

    // Vérifier qu'il n'y a pas d'éléments supplémentaires dans result
    if (result[i] != NULL)
    {
        printf("Test %d (%s) failed: result contains more elements than expected ❌\n", test_num, test_name);
        *passed_tests = 0;
    }

    // Libérer la mémoire allouée
    i = 0;
    while (result[i])
    {
        free(result[i]);
        i++;
    }
    free(result);
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    char *expected1[] = {"Hello", "world", NULL};
    test_split("Hello world", ' ', expected1, 1, "Split by space", &passed_tests);

    char *expected2[] = {"Hello", "world", NULL};
    test_split(" Hello world", ' ', expected2, 2, "Split by space with leading delimiter", &passed_tests);

    char *expected3[] = {"Hello", "world", NULL};
    test_split("Hello world ", ' ', expected3, 3, "Split by space with trailing delimiter", &passed_tests);

    char *expected4[] = {"Hello", "world", NULL};
    test_split("Hello  world", ' ', expected4, 4, "Split by space with multiple delimiters", &passed_tests);

    char *expected5[] = {"Hello", "world", NULL};
    test_split("Hello,world", ',', expected5, 5, "Split by comma", &passed_tests);

    char *expected6[] = {NULL};
    test_split("", ' ', expected6, 6, "Split empty string", &passed_tests);

    char *expected7[] = {"Hello world", NULL};
    test_split("Hello world", '\0', expected7, 7, "Split by null character", &passed_tests);

    char *expected8[] = {"Hell ", "orld", NULL};  // Correction ici
    test_split("Hell world", 'w', expected8, 8, "Split by 'w'", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_split ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_split ❌\n");
    }

    return 0;
}