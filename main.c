/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:16:07 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/15 14:18:25 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*prompt(t_shell *shell)
{
	char	*input;

	input = readline("minishell>");
	if (input == NULL)
	{
		ft_putstr_fd("Goodbye\n", 2);
		ft_exit(NULL, shell);
	}
	if (input[0] != '\0')
		add_history(input);
	if (ft_has_invalid_quotes(input))
	{
		ft_putstr_fd(OPEN_QUOTES, 2);
		free(input);
		return (NULL);
	}
	return (input);
}

static t_shell	*init_shell(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		ft_exit(NULL, NULL);
	shell->env_arr = NULL;
	shell->splitted = NULL;
	shell->token = NULL;
	shell->env = ft_env_to_list(envp);
	shell->exit_status = 0;
	if (shell->env == NULL)
		ft_exit(NULL, shell);
	return (shell);
}

static void	ft_parsing(char *input, t_shell *shell)
{
	int	i;

	i = 0;
	whitespace_to_space(&input);
	shell->splitted = ft_split2(input, ' ');
	if (shell->splitted == NULL)
		ft_clean_exit(input, shell);
	free (input);
	while (shell->splitted[i])
	{
		tokenizer(shell, i);
		i++;
	}
	ft_free_str_array(shell->splitted);
	refine_token_type(shell->token);
	expand(shell);
	second_refine_token_type(shell->token);
	shell->splitted = NULL;
}

static void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = prompt(shell);
		if (input == NULL)
			continue ;
		ft_parsing(input, shell);
		// [EXEC PLACEHOLDER]
		free_list(&shell->token);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = NULL;
	shell = init_shell(shell, envp);
	minishell_loop(shell);
}
