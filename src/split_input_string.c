/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:09:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/04 20:16:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		save_substring(t_list **list, char *start_ptr, char *end_ptr)
{
	char			*substring;
	t_list			*elem;
	t_substring		*substring_elem;

	if (!end_ptr)
		end_ptr = start_ptr + ft_strlen(start_ptr);
	substring = (char *)ft_strnew(sizeof(*substring) * (end_ptr - start_ptr));
	substring = strncpy(substring, start_ptr, end_ptr - start_ptr);
	substring_elem = (t_substring *)ft_memalloc(sizeof(*substring_elem));
	substring_elem->input_string = substring;
	elem = (t_list *)ft_memalloc(sizeof(*elem));
	elem->content = (void *)substring_elem;
	elem->next = NULL;
	ft_lstadd_e(list, elem);
	return ;
}

t_list			**split_input_string(char *input_string)
{
	char			*start_ptr;
	char			*end_ptr;
	t_list			**list;

	list = (t_list **)ft_memalloc(sizeof(*list));
	start_ptr = input_string;
	while (start_ptr && *start_ptr)
	{
		end_ptr = ft_strchr(start_ptr, '%');
		while (end_ptr && *(end_ptr + 1) == '%')
			end_ptr = ft_strchr(end_ptr + 2, '%');
		save_substring(list, start_ptr, end_ptr);
		start_ptr = end_ptr;
		if (start_ptr)
		{
			end_ptr = ft_strchr(start_ptr, 'd');
			save_substring(list, start_ptr, end_ptr + 1);
		}
		start_ptr = end_ptr;
		if (start_ptr)
			start_ptr += 1;
	}
	return (list);
}
