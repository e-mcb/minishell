/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:32:36 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/15 14:39:14 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ATTENTION : DOIT TOUJOURS ETRE APPELEE AVEC pwd COMME
// PREMIERE CHAINE DU TABLEAU D ARGUMENTS
// utilise un buffer de taille 1024 pour 
// éviter de malloc (on peut aussi utiliser PATH_MAX de limits.h)
// la fonction retourne le cwd quel que soit le nombre d'arguments
// le options ne sont pas à gérer. si options, la fonction affiche
// le cwd normalement. 
void	ft_pwd(char **str, t_shell *shell)
{
	char	cwd[1024];

	update_or_add("_", str[count_strings(str) - 1], shell, 0);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		shell->exit_status = 0;
	}
	else
	{
		perror("pwd");
		shell->exit_status = 1;
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell		*shell;
// 	t_envvar	*env_copy;

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (1);
// 	shell->env = NULL;
// 	shell->exit_status = 0;
// 	shell->env = ft_env_to_list(envp);
// 	char *test1[] = {"pwd", "Hello", "world", NULL};
// 	char *test2[] = {"pwd", NULL};
// 	char *test3[] = {"echo", "-L", "-n", NULL};
// 	ft_pwd(test1, shell);
// 	ft_pwd(test2, shell);
// 	// ft_pwd(test3, shell);
// 	env_copy = shell->env;
// 	while (env_copy)
// 	{
// 		printf("%s\n", env_copy->var);
// 		env_copy = env_copy->next;
// 	}
// 	return (0);
// }
