/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:29:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/03 10:45:02 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_unclosed(char *input, char *start)
{
	if (!*input)
		return (0);
	while (*input)
	{
		if (is_apo(*input))
		{
			if (apo_count(input + 1, *input))
				input += ft_strlenc(input + 1, *input) + 1;
			else
				return (2);
		}
		input++;
	}
	input--;
	while (input != start && !ft_strchr(input, '|'))
	{
		if (*input != ' ')
			break ;
		input--;
	}
	if (*input == '|' && *start != '|')
		return (3);
	return (0);
}

static char	*exit_signal(void)
{
	ft_putstr_fd("\033[Fminishell % exit\n", 2);
	return (NULL);
}

static char	*unexpected_eof(void)
{
	ft_putstr_fd("unexpected EOF while looking for matching `'", 2);
	ft_putchar_fd('"', 2);
	ft_putstr_fd("\n", 2);
	g_es = 258;
	return (ft_strdup(""));
}

char	*get_input(t_minishell *p, char *tmp, char *tmp2)
{
	char	*ret;
	int		status;

	status = 1;
	ret = NULL;
	while (status)
	{
		if (status == 1)
			tmp = readline("minishell % ");
		else
			tmp = readline("> ");
		if (!tmp && status == 1)
			return (exit_signal());
		else if (!tmp)
			return (unexpected_eof());
		if (ret && status == 2)
			tmp2 = ft_strjoin(ret, "\n");
		if (ret && status == 3)
			tmp2 = ft_strjoin(ret, " ");
		if (ret)
			free(ret);
		ret = ft_strjoinf(tmp2, tmp);
		if (!ret)
			return (malloc_error(p, 1, 1), NULL);
		status = is_unclosed(ret, ret);
	}
	return (delimit_this(ret, p, NULL));
}
