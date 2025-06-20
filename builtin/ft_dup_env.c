/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:30:55 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/18 19:39:37 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_envvar **head)
{
	t_envvar	*current;
	t_envvar	*next;

	current = *head;
	while (current)
	{
		free(current->var);
		current->var = NULL;
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

static t_envvar	*create_env_var(char *str, int exported, t_shell *shell)
{
	t_envvar	*node;

	node = malloc(sizeof(t_envvar));
	if (!node)
		ft_clean_exit(NULL, shell, NULL, NULL);
	node->var = ft_strdup(str);
	if (!node->var)
	{
		free(node);
		ft_clean_exit(NULL, shell, NULL, NULL);
	}
	node->exported = exported;
	node->next = NULL;
	return (node);
}

int	add_env_var(t_envvar **head, char *str, int exported, t_shell *shell)
{
	t_envvar	*new_node;
	t_envvar	*current;

	new_node = create_env_var(str, exported, shell);
	if (!new_node)
	{
		free_env_list(head);
		ft_clean_exit(NULL, shell, NULL, NULL);
	}
	if (!*head)
	{
		*head = new_node;
		return (1);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (1);
}

//LE DERNIER IF EST INUTILE
t_envvar	*ft_env_to_list(char **envp, t_shell *shell)
{
	t_envvar	*env;
	int			i;
	int			exported;

	if (!envp)
		return (NULL);
	env = NULL;
	i = 0;
	while (envp[i])
	{
		exported = 1;
		if (strncmp(envp[i], "_=", 2) == 0)
			exported = 0;
		if (!add_env_var(&env, envp[i], exported, shell))
		{
			free_env_list(&env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
