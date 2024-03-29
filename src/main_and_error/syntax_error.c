/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:48:50 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/04 09:28:07 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(t_minishell *p, char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	g_es = 258;
	free_everything(p, NULL);
}

int	special_no_quotes(char *s, char *set)
{
	if (!*s)
		return (0);
	if (ft_strchr(set, s[0]))
		return (1);
	else
		return (0);
}

int	check_syntax(t_minishell *p, char **arr)
{
	int	i;

	if (!ft_strncmp(arr[0], "|", 2))
		return (parse_error(p, arr[0]), 1);
	i = 0;
	while (arr[i])
	{
		if (arr[i + 1] && special_no_quotes(arr[i], "<>") \
		&& special_no_quotes(arr[i + 1], "<>|"))
			return ((parse_error(p, arr[i + 1])), 1);
		i++;
	}
	return (0);
}

int	prs_err(t_minishell *p, int i)
{
	if (!p->split_input[i + 1] || !*(p->split_input[i + 1]))
	{
		if (p->split_input[i][0] == '|')
		{
			parse_error(p, "|");
			return (1);
		}
		else
		{
			parse_error(p, "newline");
			return (1);
		}
	}
	return (0);
}
