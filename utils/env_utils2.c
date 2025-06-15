/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:46:44 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/15 14:41:50 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envvar	*copy_env_list(t_envvar *env)
{
	t_envvar	*copy;
	t_envvar	*tail;
	t_envvar	*new_node;

	copy = NULL;
	tail = NULL;
	while (env)
	{
		new_node = malloc(sizeof(t_envvar));
		if (!new_node)
			return (NULL);
		new_node->var = ft_strdup(env->var);
		new_node->next = NULL;
		if (!copy)
			copy = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		env = env->next;
	}
	return (copy);
}

void	ft_sort_env_list(t_envvar *head)
{
	int			swapped;
	t_envvar	*ptr;
	char		*tmp;

	if (!head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->var, ptr->next->var) > 0)
			{
				tmp = ptr->var;
				ptr->var = ptr->next->var;
				ptr->next->var = tmp;
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}
