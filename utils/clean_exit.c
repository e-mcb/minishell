/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:18:02 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/18 21:19:58 by sradosav         ###   ########.fr       */
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

void	free_exec_list(t_exec **exec)
{
	t_exec	*next;

	if (!exec || !*exec)
		return ;
	while (*exec)
	{
		next = (*exec)->next;
		if ((*exec)->arr)
			ft_free_str_array((*exec)->arr);
		free((*exec)->heredoc);
		if ((*exec)->fd_in > 0)
			close((*exec)->fd_in);
		if ((*exec)->fd_out > 0)
			close((*exec)->fd_out);
		free(*exec);
		*exec = next;
	}
}

void	ft_clean_exit(char *input, t_shell *shell,
	char *str_to_free, char **arr_to_free)
{
	if (str_to_free)
		free(str_to_free);
	if (arr_to_free)
		ft_free_str_array(arr_to_free);
	if (input)
		free(input);
	if (shell->env)
		free_env_list(&(shell->env));
	if (shell->env_arr)
		ft_free_str_array(shell->env_arr);
	if (shell->splitted)
		ft_free_str_array(shell->splitted);
	if (shell->token)
		free_list(&(shell->token));
	if (shell->exec)
		free_exec_list(&(shell->exec));
	if (shell)
		free(shell);
	exit(0);
}
