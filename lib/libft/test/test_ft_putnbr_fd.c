#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_putnbr_fd`
void test_putnbr_fd(int n, int test_num, const char *test_name, int *passed_tests)
{
    int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ft_putnbr_fd(n, fd);
    close(fd);

    fd = open("test_output.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char result[1024] = {0}; // Buffer suffisamment grand pour contenir la sortie
    read(fd, result, sizeof(result) - 1);
    close(fd);

    char expected[1024];
    snprintf(expected, sizeof(expected), "%d", n);

    if (strcmp(result, expected) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected \"%s\", got \"%s\" ❌\n", test_num, test_name, expected, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    test_putnbr_fd(42, 1, "Print positive number", &passed_tests);
    test_putnbr_fd(-42, 2, "Print negative number", &passed_tests);
    test_putnbr_fd(0, 3, "Print zero", &passed_tests);
    test_putnbr_fd(2147483647, 4, "Print INT_MAX", &passed_tests);
    test_putnbr_fd(-2147483648, 5, "Print INT_MIN", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_putnbr_fd ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_putnbr_fd ❌\n");
    }

    // Supprimer le fichier de sortie de test
    remove("test_output.txt");

    return 0;
}