/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:29:36 by treeps            #+#    #+#             */
/*   Updated: 2023/05/02 12:29:39 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void		*(*original_malloc)(size_t);

	original_malloc = dlsym(RTLD_NEXT, "malloc");
	if (g_intercept)
	{
		ft_putstr_fd("malloc was intercepted and returned NULL\n", 2);
		return (NULL);
	}
	return (original_malloc(size));
}
