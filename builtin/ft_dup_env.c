/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:30:55 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/15 13:17:33 by mzutter          ###   ########.fr       */
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

static t_envvar	*create_env_var(char *str, int exported)
{
	t_envvar	*node;

	node = malloc(sizeof(t_envvar));
	if (!node)
		return (NULL);
	node->var = ft_strdup(str);
	if (!node->var)
	{
		free(node);
		return (NULL);
	}
	node->exported = exported;
	node->next = NULL;
	return (node);
}

static int	add_env_var(t_envvar **head, char *str, int exported)
{
	t_envvar	*new_node;
	t_envvar	*current;

	new_node = create_env_var(str, exported);
	if (!new_node)
		return (0);
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

t_envvar	*ft_env_to_list(char **envp)
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
		if (!add_env_var(&env, envp[i], exported))
		{
			free_env_list(&env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
