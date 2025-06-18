/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:31:52 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/18 19:42:20 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// deux solutions pour gérer env avec arguments ou options:
// - soit faire le env et ignorer ce qu'il y a apres
// -soit envoyer une erreur s'il y a argument ou option
// dans cette version, je prefere envoyer une erreur.
// le sujet dit env sans option sans arguments.
void	ft_env(char **str, t_shell *shell)
{
	int			str_size;
	t_envvar	*env_copy;

	str_size = count_strings(str);
	if (str_size > 1)
	{
		ft_putstr_fd("minishell: env: too many arguments or options\n", 2);
		update_or_add("_", str[str_size - 1], shell, 0);
		shell->exit_status = 1;
	}
	else
	{
		env_copy = shell->env;
		while (env_copy)
		{
			if (env_copy->exported == 1 && ft_strchr(env_copy->var, '=')
				&& ft_strncmp(env_copy->var, "_=", 2) != 0)
			{
				printf("%s\n", env_copy->var);
			}
			env_copy = env_copy->next;
		}
		update_or_add("_", str[str_size - 1], shell, 0);
		shell->exit_status = 0;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell		*shell;

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (1);
// 	shell->env = NULL;
// 	shell->exit_status = 0;
// 	char *test1[] = {"env", "Hello", "world", NULL};
// 	char *test2[] = {"env", "-i", NULL};
// 	char *test3[] = {"env", NULL};

// 	shell->env = ft_env_to_list(envp);

// 	printf("Test 1:\n");
// 	ft_env(test1, shell);

// 	printf("Test 2:\n");
// 	ft_env(test2, shell);

// 	printf("Test 3:\n");
// 	ft_env(test3, shell);

// 	return 0;
// }