/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countsegments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:35:14 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/15 14:20:30 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process_single_quote(t_expand *ex)
{
	if (ex->i > ex->start)
		ex->count++;
	ex->in_single_quote = !ex->in_single_quote;
	ex->i++;
	ex->start = ex->i;
}

static void	process_double_quote(t_expand *ex)
{
	if (ex->i > ex->start)
		ex->count++;
	ex->in_double_quote = !ex->in_double_quote;
	ex->i++;
	ex->start = ex->i;
}

static void	process_dollar(const char *input, t_expand *ex)
{
	if (ex->i > ex->start)
		ex->count++;
	ex->i++;
	while (input[ex->i] && (ft_isalnum(input[ex->i]) || input[ex->i] == '_'))
		ex->i++;
	ex->count++;
	ex->start = ex->i;
}

int	ft_count_segments(const char *input)
{
	t_expand	ex;

	ex.i = 0;
	ex.j = 0;
	ex.count = 0;
	ex.start = 0;
	ex.in_single_quote = 0;
	ex.in_double_quote = 0;
	ex.result = NULL;
	while (input[ex.i])
	{
		if (input[ex.i] == '\'' && !ex.in_double_quote)
			process_single_quote(&ex);
		else if (input[ex.i] == '"' && !ex.in_single_quote)
			process_double_quote(&ex);
		else if (input[ex.i] == '$' && !ex.in_single_quote)
			process_dollar(input, &ex);
		else
			ex.i++;
	}
	if (ex.i > ex.start)
		ex.count++;
	return (ex.count);
}
