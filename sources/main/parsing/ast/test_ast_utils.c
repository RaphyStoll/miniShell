#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../includes/main/ast.h"  // Ce fichier doit contenir la définition de t_type, t_node et t_redirection


// ================================
// Tests pour create_node
// ================================
static int test_create_node(void)
{
    int total_errors = 0, errors = 0;
    t_node *node = NULL;

    // Test 1 : Création avec arguments valides (commande)
    errors = 0;
    printf("Test create_node (valid args): ");
    {
        char **args = malloc(sizeof(char*) * 3);
        if (!args)
        {
            printf(RED "Erreur d'allocation pour args\n" RESET);
            return 1;
        }
        args[0] = strdup("ls");
        args[1] = strdup("-l");
        args[2] = NULL;

        // Utilisation de WORD pour représenter une commande
        node = create_node(WORD, args);
        if (!node)
            errors++;
        else
        {
            if (node->type != WORD)
                errors++;
            if (!node->args)
                errors++;
            else if (strcmp(node->args[0], "ls") != 0 || strcmp(node->args[1], "-l") != 0)
                errors++;
            if (node->child != NULL || node->brother != NULL || node->redirections != NULL)
                errors++;
        }
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED with %d error(s)\n" RESET, errors);
        total_errors += errors;
        if (node)
        {
            free(node->args[0]);
            free(node->args[1]);
            free(node->args);
            free(node);
        }
    }

    // Test 2 : Création avec args NULL
    errors = 0;
    printf("Test create_node (NULL args): ");
    {
        node = create_node(WORD, NULL);
        if (!node)
            errors++;
        else
        {
            if (node->args != NULL)
                errors++;
            if (node->child != NULL || node->brother != NULL || node->redirections != NULL)
                errors++;
        }
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED with %d error(s)\n" RESET, errors);
        total_errors += errors;
        free(node);
    }

    // Test 3 : Création avec un tableau d'args vide (seulement NULL)
    errors = 0;
    printf("Test create_node (empty args): ");
    {
        char **args_empty = malloc(sizeof(char*));
        if (!args_empty)
        {
            printf(RED "Erreur d'allocation pour args_empty\n" RESET);
            errors++;
        }
        else
        {
            args_empty[0] = NULL;
            node = create_node(WORD, args_empty);
            if (!node)
                errors++;
            else if (node->args[0] != NULL)
                errors++;
            free(args_empty);
            free(node);
        }
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED with %d error(s)\n" RESET, errors);
        total_errors += errors;
    }

    // Test 4 : Création multiple pour vérifier l'indépendance des nœuds
    errors = 0;
    printf("Test create_node (multiple nodes indépendants): ");
    {
        char **args1 = malloc(sizeof(char*) * 2);
        args1[0] = strdup("cmd1");
        args1[1] = NULL;
        t_node *node1 = create_node(WORD, args1);

        char **args2 = malloc(sizeof(char*) * 2);
        args2[0] = strdup("cmd1");  // Même valeur pour vérifier l'indépendance
        args2[1] = NULL;
        t_node *node2 = create_node(WORD, args2);

        if (strcmp(node1->args[0], node2->args[0]) == 0)
        {
            // On s'assure que les nœuds sont distincts même si les valeurs sont identiques
            if (node1 == node2)
                errors++;
        }
        free(node1->args[0]); free(node1->args); free(node1);
        free(node2->args[0]); free(node2->args); free(node2);

        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED with %d error(s)\n" RESET, errors);
    }
    total_errors += errors;

    // Test 5 : Passage d'une valeur inattendue pour le type
    errors = 0;
    printf("Test create_node (type inattendu): ");
    {
        char **args = malloc(sizeof(char*) * 2);
        args[0] = strdup("invalid");
        args[1] = NULL;
        t_node *node_invalid = create_node((t_type)999, args);
        if (!node_invalid)
            errors++;
        else if (node_invalid->type != 999)
            errors++;
        free(node_invalid->args[0]);
        free(node_invalid->args);
        free(node_invalid);
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED with %d error(s)\n" RESET, errors);
    }
    total_errors += errors;

    return total_errors;
}

// ================================
// Tests pour add_child
// ================================
static int test_add_child(void)
{
    int total_errors = 0, errors = 0;
    t_node *parent = NULL, *child1 = NULL, *child2 = NULL, *child3 = NULL;

    // Cas d'erreur : parent NULL
    errors = 0;
    printf("Test add_child (parent NULL): ");
    {
        child1 = create_node(WORD, NULL);
        add_child(NULL, child1);  // Doit gérer sans crash
        if (!child1)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);
        free(child1);
    }
    total_errors += errors;

    // Cas d'erreur : child NULL
    errors = 0;
    printf("Test add_child (child NULL): ");
    {
        parent = create_node(PIPE, NULL);
        add_child(parent, NULL);
        if (parent->child != NULL)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);
        free(parent);
    }
    total_errors += errors;

    // Cas normal : ajout d'un premier enfant
    errors = 0;
    printf("Test add_child (premier enfant): ");
    {
        parent = create_node(PIPE, NULL);
        char **args1 = malloc(sizeof(char*) * 2);
        args1[0] = strdup("echo");
        args1[1] = NULL;
        child1 = create_node(WORD, args1);
        add_child(parent, child1);
        if (parent->child != child1)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);
        if (child1->args)
        {
            free(child1->args[0]);
            free(child1->args);
        }
        free(child1);
        free(parent);
    }
    total_errors += errors;

    // Cas normal : ajout de plusieurs enfants (3 enfants)
    errors = 0;
    printf("Test add_child (3 enfants, vérification du chaînage): ");
    {
        parent = create_node(PIPE, NULL);
        // Création du premier enfant
        char **args1 = malloc(sizeof(char*) * 2);
        args1[0] = strdup("cmd1");
        args1[1] = NULL;
        child1 = create_node(WORD, args1);
        add_child(parent, child1);

        // Création du deuxième enfant
        char **args2 = malloc(sizeof(char*) * 2);
        args2[0] = strdup("cmd2");
        args2[1] = NULL;
        child2 = create_node(WORD, args2);
        add_child(parent, child2);

        // Création du troisième enfant
        char **args3 = malloc(sizeof(char*) * 2);
        args3[0] = strdup("cmd3");
        args3[1] = NULL;
        child3 = create_node(WORD, args3);
        add_child(parent, child3);

        // Vérification du chaînage
        if (parent->child != child1)
            errors++;
        if (child1->brother != child2)
            errors++;
        if (child2->brother != child3)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);

        if (child1->args) { free(child1->args[0]); free(child1->args); }
        if (child2->args) { free(child2->args[0]); free(child2->args); }
        if (child3->args) { free(child3->args[0]); free(child3->args); }
        free(child1); free(child2); free(child3); free(parent);
    }
    total_errors += errors;

    return total_errors;
}

// ================================
// Tests pour add_brother
// ================================
static int test_add_brother(void)
{
    int total_errors = 0, errors = 0;
    t_node *node = NULL, *brother1 = NULL, *brother2 = NULL, *brother3 = NULL;

    // Cas d'erreur : node NULL
    errors = 0;
    printf("Test add_brother (node NULL): ");
    {
        brother1 = create_node(WORD, NULL);
        add_brother(NULL, brother1); // Doit gérer sans crash
        if (!brother1)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);
        free(brother1);
    }
    total_errors += errors;

    // Cas d'erreur : brother NULL
    errors = 0;
    printf("Test add_brother (brother NULL): ");
    {
        char **args = malloc(sizeof(char*) * 2);
        args[0] = strdup("cmd1");
        args[1] = NULL;
        node = create_node(WORD, args);
        add_brother(node, NULL);
        if (node->brother != NULL)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);
        free(node->args[0]);
        free(node->args);
        free(node);
    }
    total_errors += errors;

    // Cas normal : ajout d'un frère unique
    errors = 0;
    printf("Test add_brother (ajout d'un frère): ");
    {
        char **args = malloc(sizeof(char*) * 2);
        args[0] = strdup("cmd1");
        args[1] = NULL;
        node = create_node(WORD, args);

        char **argsB1 = malloc(sizeof(char*) * 2);
        argsB1[0] = strdup("cmd2");
        argsB1[1] = NULL;
        brother1 = create_node(WORD, argsB1);
        add_brother(node, brother1);
        if (node->brother != brother1)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);

        free(node->args[0]);
        free(node->args);
        free(node);
        free(brother1->args[0]);
        free(brother1->args);
        free(brother1);
    }
    total_errors += errors;

    // Cas normal : ajout de plusieurs frères successifs (3 frères)
    errors = 0;
    printf("Test add_brother (3 frères, ordre vérifié): ");
    {
        char **args = malloc(sizeof(char*) * 2);
        args[0] = strdup("cmd1");
        args[1] = NULL;
        node = create_node(WORD, args);

        char **argsB1 = malloc(sizeof(char*) * 2);
        argsB1[0] = strdup("cmd2");
        argsB1[1] = NULL;
        brother1 = create_node(WORD, argsB1);
        add_brother(node, brother1);

        char **argsB2 = malloc(sizeof(char*) * 2);
        argsB2[0] = strdup("cmd3");
        argsB2[1] = NULL;
        brother2 = create_node(WORD, argsB2);
        add_brother(node, brother2);

        char **argsB3 = malloc(sizeof(char*) * 2);
        argsB3[0] = strdup("cmd4");
        argsB3[1] = NULL;
        brother3 = create_node(WORD, argsB3);
        add_brother(node, brother3);

        // Vérification de l'ordre
        if (node->brother != brother1)
            errors++;
        if (brother1->brother != brother2)
            errors++;
        if (brother2->brother != brother3)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);

        free(node->args[0]);
        free(node->args);
        free(node);
        free(brother1->args[0]);
        free(brother1->args);
        free(brother1);
        free(brother2->args[0]);
        free(brother2->args);
        free(brother2);
        free(brother3->args[0]);
        free(brother3->args);
        free(brother3);
    }
    total_errors += errors;
    return total_errors;
}

// ================================
// Tests pour add_redirection
// ================================
static int test_add_redirection(void)
{
    int total_errors = 0, errors = 0;
    t_node *cmd = NULL;
    t_redirection *redir = NULL, *redir1 = NULL, *redir2 = NULL, *redir3 = NULL;

    // Cas d'erreur : cmd NULL
    errors = 0;
    printf("Test add_redirection (cmd NULL): ");
    {
        redir = malloc(sizeof(t_redirection));
        // On utilise REDIRECT_OUT pour la redirection par exemple
        redir->type = REDIRECT_OUT;
        redir->target = strdup("output.txt");
        redir->next = NULL;
        add_redirection(NULL, redir);
        // Vérification minimale : s'assurer que ça ne plante pas
        if (!redir)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);
        free(redir->target);
        free(redir);
    }
    total_errors += errors;

    // Cas d'erreur : redir NULL
    errors = 0;
    printf("Test add_redirection (redir NULL): ");
    {
        cmd = create_node(WORD, NULL);
        add_redirection(cmd, NULL);
        if (cmd->redirections != NULL)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);
        free(cmd);
    }
    total_errors += errors;

    // Cas normal : ajout d'une première redirection
    errors = 0;
    printf("Test add_redirection (1ère redirection): ");
    {
        char **args = malloc(sizeof(char*) * 2);
        args[0] = strdup("ls");
        args[1] = NULL;
        cmd = create_node(WORD, args);

        redir1 = malloc(sizeof(t_redirection));
        redir1->type = REDIRECT_OUT;
        redir1->target = strdup("output.txt");
        redir1->next = NULL;
        add_redirection(cmd, redir1);
        if (cmd->redirections != redir1)
            errors++;
        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);

        free(cmd->args[0]);
        free(cmd->args);
        free(cmd);
        // La redirection redir1 sera libérée dans le chaînage suivant ou séparément
    }
    total_errors += errors;

    // Cas normal : chaînage de plusieurs redirections (3 redirections)
    errors = 0;
    printf("Test add_redirection (chaînage 3 redirections): ");
    {
        char **args = malloc(sizeof(char*) * 2);
        args[0] = strdup("cat");
        args[1] = NULL;
        cmd = create_node(WORD, args);

        redir1 = malloc(sizeof(t_redirection));
        redir1->type = REDIRECT_IN;
        redir1->target = strdup("file1.txt");
        redir1->next = NULL;
        add_redirection(cmd, redir1);

        redir2 = malloc(sizeof(t_redirection));
        redir2->type = REDIRECT_OUT;
        redir2->target = strdup("file2.txt");
        redir2->next = NULL;
        add_redirection(cmd, redir2);

        redir3 = malloc(sizeof(t_redirection));
        redir3->type = HEREDOC;
        redir3->target = strdup("file3.txt");
        redir3->next = NULL;
        add_redirection(cmd, redir3);

        // Vérification du chaînage
        if (cmd->redirections == NULL)
            errors++;
        else if (cmd->redirections->next != redir2)
            errors++;
        else if (redir2->next != redir3)
            errors++;

        if (errors == 0)
            printf(LIGHT_GREEN "OK\n" RESET);
        else
            printf(LIGHT_RED "FAILED\n" RESET);

        free(cmd->args[0]);
        free(cmd->args);
        free(cmd);
        free(redir1->target);
        free(redir1);
        free(redir2->target);
        free(redir2);
        free(redir3->target);
        free(redir3);
    }
    total_errors += errors;
    return total_errors;
}

// ================================
// Fonction main : exécute les tests et affiche chaque test unitaire
// ================================
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s [1|2|3|4|all]\n", argv[0]);
        return 1;
    }
    int total_errors = 0, errors = 0;

    if (strcmp(argv[1], "all") == 0)
    {
        printf("======== Tests pour create_node ========\n");
        errors = test_create_node();
        printf("Total errors in create_node: %d\n", errors);
        total_errors += errors;
        printf("==========================================\n\n");

        printf("======== Tests pour add_child ========\n");
        errors = test_add_child();
        printf("Total errors in add_child: %d\n", errors);
        total_errors += errors;
        printf("========================================\n\n");

        printf("======== Tests pour add_brother ========\n");
        errors = test_add_brother();
        printf("Total errors in add_brother: %d\n", errors);
        total_errors += errors;
        printf("==========================================\n\n");

        printf("======== Tests pour add_redirection ========\n");
        errors = test_add_redirection();
        printf("Total errors in add_redirection: %d\n", errors);
        total_errors += errors;
        printf("===============================================\n\n");
    }
    else
    {
        int choix = atoi(argv[1]);
        switch (choix)
        {
            case 1:
                total_errors = test_create_node();
                break;
            case 2:
                total_errors = test_add_child();
                break;
            case 3:
                total_errors = test_add_brother();
                break;
            case 4:
                total_errors = test_add_redirection();
                break;
            default:
                printf("Option invalide. Choisissez 1, 2, 3, 4 ou 'all'.\n");
                return 1;
        }
    }
    if (total_errors == 0)
        printf(LIGHT_GREEN "Tous les tests se sont terminés avec succès.\n" RESET);
    else
        printf(LIGHT_RED "Échec de certains tests avec %d erreur(s) détectée(s).\n" RESET, total_errors);
    return total_errors;
}
