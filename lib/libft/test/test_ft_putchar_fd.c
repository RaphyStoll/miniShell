#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_putchar_fd`
void test_putchar_fd(char c, int test_num, const char *test_name, int *passed_tests)
{
    int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ft_putchar_fd(c, fd);
    close(fd);

    fd = open("test_output.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char result;
    read(fd, &result, 1);
    close(fd);

    if (result != c)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected '%c', got '%c' ❌\n", test_num, test_name, c, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    test_putchar_fd('a', 1, "Print 'a'", &passed_tests);
    test_putchar_fd('Z', 2, "Print 'Z'", &passed_tests);
    test_putchar_fd('0', 3, "Print '0'", &passed_tests);
    test_putchar_fd('\n', 4, "Print newline", &passed_tests);
    test_putchar_fd('!', 5, "Print exclamation mark", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_putchar_fd ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_putchar_fd ❌\n");
    }

    // Supprimer le fichier de sortie de test
    remove("test_output.txt");

    return 0;
}