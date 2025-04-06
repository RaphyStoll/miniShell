#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env_struct.h"
#include "utils.h"
// ---------- UTILS ----------

t_env *new_env_node(const char *type, const char *value)
{
	t_env *node = calloc(1, sizeof(t_env));
	if (!node)
		return NULL;
	node->type = strdup(type);
	node->value = value ? strdup(value) : NULL;
	node->next = NULL;
	return node;
}

void print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->type, env->value ? env->value : "(null)");
		env = env->next;
	}
}

void free_env(t_env *env)
{
	t_env *tmp;

	if (!env)
		return NULL;
	while (env)
	{
		tmp = env->next;
		free(env->type);
		free(env->value);
		free(env);
		env = tmp;
	}
}

// ---------- PARSE ENV ----------

t_env *env_from_array(char **envp)
{
	t_env *head = NULL;
	t_env *last = NULL;
	char *equal;
	char *key;
	char *value;

	while (*envp)
	{
		equal = strchr(*envp, '=');
		if (!equal)
		{
			envp++;
			continue;
		}

		size_t key_len = equal - *envp;
		key = strndup(*envp, key_len);
		value = strdup(equal + 1);

		t_env *new_node = new_env_node(key, value);
		free(key);
		free(value);

		if (!head)
			head = new_node;
		else
			last->next = new_node;
		last = new_node;

		envp++;
	}
	return head;
}

// ---------- MAIN ----------

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_env *env_list = env_from_array(envp);

	printf("Before sort:\n");
	print_env_list(env_list);

	sort_env(&env_list);

	printf("\nAfter sort:\n");
	print_env_list(env_list);

	free_env(env_list);
	return 0;
}