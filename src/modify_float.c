/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:01:45 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 18:22:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*conv_float(va_list *ap, t_substring *substring,
															int *attrs)
{
	long double		nbr;
	char			*s;
	size_t			precision;
	int				add_dot;

	(*attrs)++;
	add_dot = substring->flags & hash;
	if (!substring->param_type)
		nbr = (double)va_arg(*ap, double);
	else
		nbr = read_f_param(substring->param_type->type, ap);
	if (substring->precision == -1)
		precision = 6;
	else
		precision = substring->precision;
	s = ft_dtoa_base(nbr, 10, precision, add_dot);
	return (s);
}

void					adjust_float(t_substring *substring)
{
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}
