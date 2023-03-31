/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:38:44 by treeps            #+#    #+#             */
/*   Updated: 2023/01/19 16:38:46 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == 32 || (str[*i] > 8 && str[*i] < 14))
		(*i)++;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (sign);
}

double	ft_atof(const char *str)
{
	int			i;
	int			sign;
	double		result;
	int			e;

	e = 0;
	i = 0;
	sign = get_sign(str, &i);
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	if (str[i++] == '.')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + str[i++] - '0';
			e -= 1;
		}
	}
	while (e++ < 0)
		result *= 0.1;
	return (result * sign);
}
