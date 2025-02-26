#include "../header/libft.h"

// Fonction pour exécuter les tests de `ft_putstr_fd`
void test_putstr_fd(char *s, int test_num, const char *test_name, int *passed_tests)
{
    int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ft_putstr_fd(s, fd);
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

    if (strcmp(result, s) != 0)
    {
        // Test échoué
        printf("Test %d (%s) failed: expected \"%s\", got \"%s\" ❌\n", test_num, test_name, s, result);
        *passed_tests = 0;
    }
}

int main(void)
{
    int passed_tests = 1;

    // Déclaration des tests
    char str1[] = "Hello, world!";
    char str2[] = "";
    char str3[] = "42";
    char str4[] = "!@#$%^&*()";
    char str5[] = "This is a longer test string.";

    test_putstr_fd(str1, 1, "Print 'Hello, world!'", &passed_tests);
    test_putstr_fd(str2, 2, "Print empty string", &passed_tests);
    test_putstr_fd(str3, 3, "Print '42'", &passed_tests);
    test_putstr_fd(str4, 4, "Print special characters", &passed_tests);
    test_putstr_fd(str5, 5, "Print longer string", &passed_tests);

    // Afficher le résultat global des tests
    if (passed_tests)
    {
        printf("All tests passed for ft_putstr_fd ✅\n");
    }
    else
    {
        printf("Some tests failed for ft_putstr_fd ❌\n");
    }

    // Supprimer le fichier de sortie de test
    remove("test_output.txt");

    return 0;
}