/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:48:35 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/04 14:29:28 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:39:58 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/02 17:28:25 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_min(int x, int y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}

static void	delim_helper(t_minishell *p, char *delim)
{
	char	*tmp;
	char	*to_free;

	tmp = readline("> ");
	to_free = tmp;
	tmp = ft_strjoin(tmp, "\n");
	free(to_free);
	while (ft_strncmp(tmp, delim, ft_strlen(delim)))
	{
		to_free = p->heredoc;
		p->heredoc = ft_strjoin(p->heredoc, tmp);
		free(to_free);
		free(tmp);
		tmp = readline("> ");
		if (!tmp)
		{
			ft_putstr_fd("\033[A> ", 2);
			break ;
		}
		to_free = tmp;
		tmp = ft_strjoin(tmp, "\n");
		free(to_free);
	}
	if (tmp)
		free(tmp);
}

char	*delimit_this(char *s, t_minishell *p, char *delim)
{
	char	*loc;
	int		len;

	loc = ft_strnstr(s, "<<", ft_strlen(s));
	if (!loc || *(loc + 2) == '<' || *(loc + 2) == '>' || !*(loc + 2))
		return (s);
	p->heredoc = ft_strdup("");
	while (loc)
	{
		while (*(loc + 2) == ' ')
			loc++;
		len = ft_min(ft_strlenc(loc + 2, ' '), ft_strlenc(loc + 2, '\n'));
		delim = malloc(len + 2);
		ft_strlcpy(delim, loc + 2, len + 1);
		delim[len + 1] = 0;
		delim[len] = '\n';
		delim_helper(p, delim);
		loc = ft_strnstr(loc + 2, "<<", ft_strlen(loc + 2));
		free(delim);
		delim = NULL;
	}
	if (p->heredoc)
		p->heredoc = expand_variables(p, p->heredoc, NULL, 0);
	return (s);
}

void	open_heredoc_pipe(t_minishell *p)
{
	pipe(&p->hd_pipe[0]);
	write(p->hd_pipe[1], p->heredoc, ft_strlen(p->heredoc));
	close(p->hd_pipe[1]);
}
