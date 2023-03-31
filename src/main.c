/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/03/31 17:58:16 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_unclosed(char *input)
{
	while (*input)
	{
		if (is_apo(*input))
		{
			if (apo_count(input + 1, *input))
				input += mod_ft_strlen(input + 1, *input) + 2;
			else
				return (1);
		}
		input++;
	}
	return (0);
}

static char	*get_input(int unclosed)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;
	int		size;

	ret = NULL;
	tmp2 = NULL;
	unclosed = 1;
	while (unclosed)
	{
		tmp = ft_get_next_line(0);
		if (ret)
			tmp2 = ft_strdup(ret);
		free(ret);
		size = ft_strlen(tmp) + ft_strlen(tmp2) + 1;
		ret = ft_calloc(size, 1);
		ft_strlcat(ret, tmp2, size);
		ft_strlcat(ret, tmp, size);
		free(tmp);
		if (tmp2)
			free(tmp2);
		unclosed = is_unclosed(ret);
	}
	return (ret);
}

int	main(void)
{
	char	**parsed_input;
	char	*input;
	
	input = get_input(1);
	
	ft_printf("final input string: %s", input);
	parsed_input = ft_shell_split(input, 32);
	print_array(parsed_input);
	free_arr(parsed_input);
	free(input);
	return (0);
}
