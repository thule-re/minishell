/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:41:17 by awilliam          #+#    #+#             */
/*   Updated: 2023/03/31 19:00:48 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

char	**ft_shell_split(char *s, char c);
int		apo_count(char *str, char apo);
int		is_apo(char c);
char	next_one(char *s);
void	free_strings(char **result, int index);
void	free_arr(char **arr);
void	print_array(char **arr);
int		mod_ft_strlen(char *str, char c);

#endif
