/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:43:39 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/18 19:35:58 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_var_exists(char *var, t_shell *shell)
{
	size_t		len;
	char		*var_equal;
	t_envvar	*copy_env;

	if (!var || !shell || !shell->env)
		return (0);
	var_equal = ft_strjoin(var, "=");
	if (!var_equal)
		ft_clean_exit(NULL, shell, NULL, NULL);
	len = ft_strlen(var);
	copy_env = shell->env;
	while (copy_env)
	{
		if (ft_strcmp(copy_env->var, var) == 0)
			return (free(var_equal), 1);
		if (ft_strncmp(copy_env->var, var_equal, len + 1) == 0)
			return (free(var_equal), 1);
		copy_env = copy_env->next;
	}
	free(var_equal);
	return (0);
}

void	update_env(char *var, char *str, t_shell *shell)
{
	char		*full_var;
	char		*new_var;
	t_envvar	*copy_env;
	size_t		len;

	full_var = ft_strjoin(var, "=");
	if (!full_var)
		ft_clean_exit(NULL, shell, NULL, NULL);
	len = ft_strlen(full_var);
	copy_env = shell->env;
	while (copy_env)
	{
		if (envvar_match(copy_env->var, var, len, full_var))
		{
			free(copy_env->var);
			new_var = ft_strjoin(full_var, str);
			if (!new_var)
				ft_clean_exit(NULL, shell, full_var, NULL);
			copy_env->var = new_var;
			free(full_var);
			return ;
		}
		copy_env = copy_env->next;
	}
	free(full_var);
}

void	update_or_add(char *var, char *str, t_shell *shell, int exported)
{
	char	*temp;
	char	*temp2;
	int		exists;

	exists = env_var_exists(var, shell);
	if (exists == 1)
		update_env(var, str, shell);
	else
	{
		temp = ft_strjoin(var, "=");
		if (!temp)
			ft_clean_exit(NULL, shell, NULL, NULL);
		temp2 = ft_strjoin(temp, str);
		free(temp);
		if (!temp2)
			ft_clean_exit(NULL, shell, NULL, NULL);
		add_env_var(&(shell->env), temp2, exported, shell);
		free(temp2);
	}
	return ;
}

char	*ft_getenv(char *var, t_shell *shell)
{
	size_t		len;
	char		*entry;
	t_envvar	*env_copy;

	if (!var)
		return (NULL);
	len = ft_strlen(var);
	env_copy = shell->env;
	while (env_copy)
	{
		entry = env_copy->var;
		if (ft_strncmp(entry, var, len) == 0 && entry[len] == '=')
			return (entry + len + 1);
		env_copy = env_copy->next;
	}
	return (NULL);
}
