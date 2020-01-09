/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:35:39 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 21:36:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		del_formatter(void *formatter, size_t size)
{
	(void)size;
	free(formatter);
	formatter = NULL;
	return ;
}

static void		reset_elem(t_list *elem)
{
	char	*s;

	if ((*elem).content_size)
	{
		s = (*elem).content;
		ft_strdel(&s);
		(*elem).content_size = 0;
		(*elem).next = NULL;
	}
	return ;
}

static void		del_o_string(t_substring *elem)
{
	reset_elem(&elem->o_string.pre_filler);
	reset_elem(&elem->o_string.sign);
	reset_elem(&elem->o_string.prefix);
	reset_elem(&elem->o_string.zero_filler);
	reset_elem(&elem->o_string.parameter);
	reset_elem(&elem->o_string.post_filler);
}

static void		del_substring(void *substring_elem, size_t size)
{
	t_substring		*elem;

	(void)size;
	elem = (t_substring *)substring_elem;
	ft_strdel(&elem->input_string);
	if (elem->formatter_list)
	{
		ft_lstdel(elem->formatter_list, *del_formatter);
		free(elem->formatter_list);
		elem->formatter_list = NULL;
		del_o_string(elem);
		elem->formatter_list = NULL;
	}
	free(substring_elem);
	substring_elem = NULL;
	return ;
}

static void		del_converter(void *converter, size_t size)
{
	(void)size;
	free(converter);
	converter = NULL;
	return ;
}

static void		del_param_type(void *type, size_t size)
{
	(void)size;
	free(type);
	type = NULL;
	return ;
}

void			release_memory(t_list **substring_list, t_list **converter_list,
									t_list **formatter_list, t_list **type_list)
{
	ft_lstdel(substring_list, *del_substring);
	free(substring_list);
	substring_list = NULL;
	ft_lstdel(converter_list, *del_converter);
	free(converter_list);
	converter_list = NULL;
	ft_lstdel(formatter_list, *del_formatter);
	free(formatter_list);
	formatter_list = NULL;
	ft_lstdel(type_list, *del_param_type);
	free(type_list);
	type_list = NULL;
	return ;
}
