/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:48:35 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/04 12:45:06 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:31:14 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/03 12:26:07 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_count(char *str, char apo_type, int i, int count)
{
	if (!str || !*str)
		return (0);
	if (str[i + 1] != ' ')
		count++;
	while (str[++i])
	{
		if (is_apo(str[i]) && apo_count(&str[i + 1], str[i]))
		{
			apo_type = str[i++];
			while (str[i] != apo_type)
				i++;
			i++;
		}
		if (!str[i])
			break ;
		if (str[i] == ' ' && str[i + 1] != ' ')
			count++;
		if (ft_strchr("<>|", str[i]))
		{
			count += 2;
			i++;
		}
	}
	return (count);
}

static int	shell_split_helper(char *s, char **result, int i)
{
	int		len;

	len = 0;
	while (s[len] && s[len] != ' ')
	{
		if (ft_strchr("<>|", s[len]) && len)
			break ;
		if (ft_strchr("<>|", s[len]) && !len)
		{
			len++;
			if (s[len] == s[len - 1] \
			|| (s[len] == '>' && s[len - 1] == '<'))
				len++;
			break ;
		}
		if (is_apo(s[len]))
			len += ft_strlenc(&s[len + 1], s[len]) + 1;
		len++;
	}
	result[i] = malloc(len + 1);
	if (result[i])
		ft_strlcpy(result[i], s, len + 1);
	return (ft_strlen(result[i]));
}

char	**ft_shell_split(t_minishell *p, char *s, char c)
{
	char	**result;
	int		i;
	int		count;

	i = 0;
	count = word_count(s, c, -1, 0);
	result = malloc((count + 1) * sizeof(char *));
	if (result == NULL)
		return (0);
	while (*s == c && *s)
		s++;
	while (*s && i < count)
	{
		s += shell_split_helper(s, result, i);
		if (!result[i] || !s)
		{
			free_strings(result, i);
			return (0);
		}
		while (*s == c && *s)
			s++;
		i++;
	}
	result[i] = 0;
	return (reformat_inputs(p, result, 0));
}
