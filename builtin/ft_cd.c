/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:30:37 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/18 19:21:50 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ATTENTION : DOIT TOUJOURS ETRE APPELEE AVEC cd COMME
// PREMIERE CHAINE DU TABLEAU D ARGUMENTS
// utilise un buffer de taille 1024 pour 
// éviter de malloc
// si pas pile un  argument, erreur + mise à jour de $_
// si un argument, essaie le cd , mets a jour $_ 
// traite les ~, - etc.. comme des chemins normaux
// 25 LIGNES WESH :
void	ft_cd(char **str, t_shell *shell)
{
	char	*pwd;
	char	cwd[1024];

	pwd = ft_getenv("PWD", shell);
	shell->exit_status = 1;
	if (!str[1] || str[2])
	{
		if (!str[1])
			ft_putstr_fd("minishell: cd: missing argument\n", 2);
		else
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		update_or_add("_", str[count_strings(str) - 1], shell, 0);
		return ;
	}
	if (chdir(str[1]) != 0)
	{
		perror("minishell: cd");
		update_or_add("_", str[count_strings(str) - 1], shell, 0);
		return ;
	}
	update_or_add("_", str[count_strings(str) - 1], shell, 0);
	update_or_add("OLDPWD", pwd, shell, 0);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_or_add("PWD", cwd, shell, 0);
	shell->exit_status = 0;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	cwd[1024];
// 	t_shell	*shell;
// 	t_envvar	*env_copy;

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (1);
// 	shell->env = NULL;
// 	shell->exit_status = 0;
// 	shell->env = ft_env_to_list(envp);
// 	ft_cd(argv, shell);
// 	// if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	// 	printf("Current directory: %s\n", cwd);
// 	// else
// 	// 	perror("getcwd");
// 	// env_copy = shell->env;
// 	// while (env_copy)
// 	// {
// 	// 	printf("%s\n", env_copy->var);
// 	// 	env_copy = env_copy->next;
// 	// }
// 	return (0);
// }
