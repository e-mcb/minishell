/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:31:46 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/15 11:50:17 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Renvoie 1 si l on a une chaine du type -n ou -nnnnn ou -nnnnnnnnn ...
// Sinon renvoie 0. 
// Teste les premiers arguments passés à ft_echo pour savoir si il y a 
// le -n ou pas. 
// -n enlève le \n du résultat de ft_echo
int	is_n_flag(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// check s il faut enlever le -n à la fin
// fait un printf de tous les arguments passés à ft_echo (sauf les -nnn
// s il y en a)
// met à jour la variable $_ avec le dernier argument ou la crée si 
// elle n'existe pas.
// met à jour le exit_status à 0. echo ne foire pas, si l'update 
// de $_ foire on s en fout, ca aura été print avant et dur a tester
int	ft_echo(char **str, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (str[i] && is_n_flag(str[i]))
	{
		newline = 0;
		i++;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	update_or_add("_", str[i - 1], shell->env, 0);
	shell->exit_status = 0;
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell		*shell;
// 	// t_envvar	*env_copy;

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (1);
// 	shell->env = NULL;
// 	shell->exit_status = 0;
// 	// char *test1[] = {"echo", "-n", "-nnnn      ", "world", NULL};
// 	// char *test2[] = {"echo", "-n", "Hello", "world", NULL};
// 	// char *test3[] = {"echo", "-n", "-n", "Hello", NULL};
// 	// char *test4[] = {"echo", "-n", "-wrong", "Hello", NULL};
// 	char *test5[] = {"echo", NULL};
// 	// char *test6[] = {"echo", "-nnnnnn", "-nnn", NULL};
// 	char **env;

// 	shell->env = ft_env_to_list(envp);

// 	// printf("Test 1:\n");
// 	// ft_echo(test1, shell); // => Hello world\n

// 	// printf("Test 2:\n");
// 	// ft_echo(test2, shell); // => Hello world

// 	// printf("Test 3:\n");
// 	// ft_echo(test3, shell); // => Hello

// 	// printf("Test 4:\n");
// 	// ft_echo(test4, shell); // => -wrong Hello\n

// 	printf("Test 5:\n");
// 	ft_echo(test5, shell); // => \n

// 	// printf("Test 6:\n");
// 	// ft_echo(test6, shell); // => \n

// 	// env_copy = shell->env;
// 	// while (env_copy)
// 	// {
// 	// 	printf("%s\n", env_copy->var);
// 	// 	env_copy = env_copy->next;
// 	// }

// 	return 0;
// }