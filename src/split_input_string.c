/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:09:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/04 18:10:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list				**split_input_string(char *input_string)
{
	char			*substring;
	char			*next_ptr;
	t_list			**list;
	t_list			*elem;
	t_substring		*substring_elem;

	list = (t_list **)ft_memalloc(sizeof(*list));
	next_ptr = ft_strchr(input_string, '%');
	if (next_ptr && *(next_ptr + 1) != '%')
	{
		substring = (char *)ft_strnew(sizeof(*substring) *
				(next_ptr - input_string));
		substring = strncpy(substring, input_string, next_ptr - input_string);
		substring_elem = (t_substring *)ft_memalloc(sizeof(*substring_elem));
		substring_elem->input_string = substring;
		elem = (t_list *)ft_memalloc(sizeof(*elem));
		elem->content = (void *)substring_elem;
		elem->next = NULL;
		ft_lstadd_e(list, elem);
	}
	ft_putstr(input_string);
	return (list);
}
