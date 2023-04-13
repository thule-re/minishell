/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:39:58 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/13 13:48:53 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_min(int x, int y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}

void	delim_helper(t_pipehelper *p, char *delim)
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
		to_free = tmp;
		tmp = ft_strjoin(tmp, "\n");
		free(to_free);
	}
	if (tmp)
		free(tmp);
}

char	*delimit_this(char *s, t_pipehelper *p)
{
	char	*loc;
	char	*delim;
	int		len;

	loc = ft_strnstr(s, "<<", ft_strlen(s));
	while (loc)
	{
		if (p->heredoc)
		{
			free(p->heredoc);
			p->heredoc = NULL;
		}
		len = ft_min(mod_ft_strlen(loc + 2, ' '), mod_ft_strlen(loc + 2, '\n'));
		delim = malloc(len + 2);
		ft_strlcpy(delim, loc + 2, len + 1);
		delim[len + 1] = 0;
		delim[len] = '\n';
		delim_helper(p, delim);
		loc = ft_strnstr(loc + 2, "<<", ft_strlen(loc + 2));
		free(delim);
		delim = NULL;
	}
	return (s);
}
