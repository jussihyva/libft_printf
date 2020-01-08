/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:58:22 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/08 21:37:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_pointer_parameter(t_substring *substring)
{
	char			*s;
	uintptr_t		par_value;

	par_value = *(uintptr_t *)substring->par_value;
	s = ft_lltoa_base(par_value, 16);
	if (par_value == 0 && substring->precision == 0)
		save_parameter(substring, "");
	else if (par_value < 0)
	{
		save_parameter(substring, ft_strdup(s + 1));
		ft_strdel(&s);
	}
	else
		save_parameter(substring, s);
	return ;
}

void		adjust_pointer(t_substring *substring)
{
	set_pointer_parameter(substring);
	set_sign(substring);
	set_prefix(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

char		*conv_pointer(va_list *ap, t_substring *substring, int *attrs)
{
	uintptr_t		**ptr;

	(*attrs)++;
	ptr = (uintptr_t **)ft_memalloc(sizeof(*ptr));
	*ptr = (uintptr_t *)(va_arg(*ap, void *));
	substring->par_value = ptr;
	format_string(ft_strnew(0), substring);
	return (NULL);
}
