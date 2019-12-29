/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:01:45 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 14:20:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*conv_float(va_list *ap, t_substring *substring,
															int *attrs)
{
	double			nbr;
	char			*s;
	size_t			precision;
	int				add_dot;

	(*attrs)++;
	add_dot = substring->flags & hash;
	nbr = (double)va_arg(*ap, double);
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

//	if ((int)ft_strlen(substring->output_string) < substring->width)
//	{
//		new_string = modify_substring(substring);
//		ft_strdel(&substring->output_string);
//		substring->output_string = new_string;
//	}
	return ;
}
