/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:16:12 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/08 10:22:36 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:29:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/08 09:02:08 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*put_prompt(t_minishell *p, int which, int i)
{
	char	*pwd;
	char	*tmp;
	char	**split_pwd;
	char	*line;

	pwd = ft_getenv("PWD", *p->envp);
	split_pwd = ft_split(pwd, '/');
	if (!split_pwd && !which)
		return (readline("minishell % "));
	while (split_pwd[i + 1])
		i++;
	tmp = ft_strjoin("minishell: [", split_pwd[i]);
	pwd = ft_strjoin(tmp, "] % ");
	free(tmp);
	free_arr(split_pwd);
	if (which)
	{
		ft_printf("%s", pwd);
		return (free(pwd), NULL);
	}
	line = readline(pwd);
	free(pwd);
	return (line);
}

static int	is_unclosed_helper(char *input, char *start)
{
	if (*input == '|' && *start != '|')
	{
		input--;
		while (input != start && *input == ' ')
			input--;
		if (ft_strchr("<>|", *input))
			return (0);
		else
			return (3);
	}
	return (0);
}

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
	return (is_unclosed_helper(input, start));
}

static char	*unexpected_eof(int status)
{
	if (status == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("unexpected EOF while looking for matching `'\"\n", 2);
	}
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	g_es = 258;
	return (ft_strdup(""));
}

char	*get_input(t_minishell *p, char *tmp, char *tmp2, int status)
{
	char	*ret;

	ret = NULL;
	while (status)
	{
		if (status == 1)
			tmp = put_prompt(p, 0, 0);
		else
			tmp = readline("> ");
		if (!tmp && status == 1)
			return (exit_signal(p));
		else if (!tmp)
			return (unexpected_eof(status));
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
	return (delimit_this(ret, p, NULL, 0));
}
