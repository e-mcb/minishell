/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:43:39 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/15 14:29:21 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_var_exists(char *var, t_envvar *env)
{
	size_t		len;
	char		*var_equal;
	t_envvar	*copy_env;

	if (!var || !env)
		return (0);
	var_equal = ft_strjoin(var, "=");
	if (!var_equal)
		return (-1);
	len = ft_strlen(var);
	copy_env = env;
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

void	update_env(char *var, char *str, t_envvar *env)
{
	size_t		len;
	char		*full_var;
	char		*temp;
	t_envvar	*copy_env;

	full_var = ft_strjoin(var, "=");
	len = ft_strlen(full_var);
	copy_env = env;
	while (copy_env)
	{
		if (ft_strncmp(copy_env->var, full_var, len) == 0)
		{
			free(copy_env->var);
			temp = ft_strjoin("=", str);
			copy_env->var = ft_strjoin(var, temp);
			free(temp);
			free(full_var);
			return ;
		}
		copy_env = copy_env->next;
	}
	free(full_var);
}

void	update_or_add(char *var, char *str, t_envvar *env, int exported)
{
	char	*temp;
	char	*temp2;
	int		exists;

	exists = env_var_exists(var, env);
	if (exists == 1)
		update_env(var, str, env);
	else if (exists == -1)
		return ;
	else
	{
		temp = ft_strjoin(var, "=");
		if (!temp)
			return ;
		temp2 = ft_strjoin(temp, str);
		free(temp);
		if (!temp2)
			return ;
		add_env_var(&env, temp2, exported);
		free(temp2);
	}
	return ;
}

char	*ft_getenv(char *var, t_envvar *env)
{
	size_t		len;
	char		*entry;
	t_envvar	*env_copy;

	if (!var)
		return (NULL);
	len = ft_strlen(var);
	env_copy = env;
	while (env_copy)
	{
		entry = env_copy->var;
		if (ft_strncmp(entry, var, len) == 0 && entry[len] == '=')
			return (entry + len + 1);
		env_copy = env_copy->next;
	}
	return (NULL);
}
