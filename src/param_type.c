/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:43:33 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/15 18:56:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					add_param_type(t_list **list, t_list **type_list)
{
	(void)list;
	(void)type_list;
}

static t_list			*new_type(t_type type, char *s)
{
	t_list			*type_elem;

	(void)type;
	type_elem = ft_lstnew(s, sizeof(s));
	return (type_elem);
}

t_list					**create_param_type_list(void)
{
	t_list			**type_list;

	type_list = (t_list **)ft_memalloc(sizeof(*type_list));
	ft_lstadd_e(type_list, new_type(hh, "hh"));
	ft_lstadd_e(type_list, new_type(h, "h"));
	ft_lstadd_e(type_list, new_type(l, "l"));
	ft_lstadd_e(type_list, new_type(ll, "ll"));
	ft_lstadd_e(type_list, new_type(j, "j"));
	ft_lstadd_e(type_list, new_type(z, "z"));
	ft_lstadd_e(type_list, new_type(t, "t"));
	ft_lstadd_e(type_list, new_type(L, "L"));
	return (type_list);
}
