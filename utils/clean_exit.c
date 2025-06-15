/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:18:02 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/15 14:06:32 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	ft_free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_clean_exit(char *input, t_shell *shell)
{
	if (input)
		free(input);
	if (shell->env)
		ft_free_str_array(shell->env);
	if (shell->splitted)
		ft_free_str_array(shell->splitted);
	if (shell->token)
		free_list(&(shell->token));
	if (shell)
		free(shell);
	exit(0);
}
