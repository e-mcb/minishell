/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:32:39 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/15 12:43:19 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_node(char *var_name, t_envvar **head)
{
	t_envvar	*current;
	t_envvar	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var_name, ft_strlen(var_name)) == 0
			&& current->var[ft_strlen(var_name)] == '=')
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->var);
			current->var = NULL;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

// TOUJOURS PASSER EN PREMIERE CHAINE LA COMMANDE , ICI UNSET
void	ft_unset(char **str, t_shell *shell)
{
	int	i;

	i = 1;
	while (str[i])
	{
		delete_node(str[i], &shell->env);
		i++;
	}
	update_or_add("_", str[i - 1], shell->env, 0);
	shell->exit_status = 0;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell		*shell;
// 	t_envvar	*env_copy;

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (1);
// 	shell->env = NULL;
// 	shell->exit_status = 0;
// 	char *test1[] = {"unset", "Hello", "world", NULL};
// 	char *test2[] = {"unset", "-n", "Hello", "world", NULL};
// 	char *test3[] = {"unset", "-n", "-n", "Hello", NULL};
// 	char *test4[] = {"unset", "-n", "-wrong", "Hello", NULL};
// 	char *test5[] = {"unset", NULL};
// 	char *test6[] = {"unset", "-nnnnnn", "-nnn", NULL};
//     char *test7[] = {"unset", "OLDPWD", NULL};
// 	char **env;

// 	shell->env = ft_env_to_list(envp);

// 	ft_unset(test1, shell); // ne fait rien	
// 	ft_unset(test2, shell); // ne fait rien	
// 	ft_unset(test3, shell); // ne fait rien	
// 	ft_unset(test4, shell); // ne fait rien
// 	ft_unset(test5, shell); // ne fait rien
// 	ft_unset(test6, shell); // ne fait rien
//     ft_unset(test7, shell); // SUPPRIME OLDPWD

// 	env_copy = shell->env;
// 	while (env_copy)
// 	{
// 		printf("%s\n", env_copy->var);
// 		env_copy = env_copy->next;
// 	}

// 	return 0;
// }

// void remove_var(char *var_name, char ***envp_ptr)
// {
//     char    **envp;
//     int     size;
//     int     i;
//     int     j;

//     envp = *envp_ptr;
//     size = ft_strsize(envp);
//     i = 0;
//     while (i < size)
//     {
//         if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
//             && envp[i][ft_strlen(var_name)] == '=')
//         {
//             free(envp[i]);
//             j = i;
//             while (j < size - 1)
//             {
//                 envp[j] = envp[j + 1];
//                 j++;
//             }
//             envp[size - 1] = NULL;
//             size--;
//             continue ;
//         }
//         i++;
//     }
//     return ;
// }
