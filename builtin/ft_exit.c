/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:31:57 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/15 14:35:06 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit_argcheck(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (42);
	else
		return (0);
}

int	ft_is_number(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_exit_argcheck(*str))
			return (0);
		str++;
	}
	return (1);
}

// free(shell) aussi ??
void	free_before_exit(t_shell *shell, void *ptr_a, void *ptr_b)
{
	(void) ptr_a;
	(void) ptr_b;
	if (shell)
	{
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
	}
}

int	ft_exit(char **arr, t_shell *shell)
{
	if (!arr[1])
	{
		free_before_exit(shell, NULL, NULL);
		exit(0);
	}
	else if (arr[1] && arr[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	else if (!ft_is_number(arr[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		free_before_exit(shell, NULL, NULL);
		exit (2);
	}
	else
	{
		free_before_exit(shell, NULL, NULL);
		exit (ft_atoll(arr[1]) % 256);
	}
}
