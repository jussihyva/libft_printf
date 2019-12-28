/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:01:45 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/28 16:04:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*conv_float(va_list *ap, t_substring *substring,
															int *attrs)
{
	double			nbr;
	char			*s;
	size_t			precision;

	(void)substring;
	(*attrs)++;
	nbr = (double)va_arg(*ap, double);
	precision = 6;
	s = ft_dtoa_base(nbr, 10, precision);
	return (s);
}

void					adjust_float(t_substring *substring)
{
	char		*new_string;

	if ((int)ft_strlen(substring->output_string) < substring->width)
	{
		new_string = modify_substring(substring);
		ft_strdel(&substring->output_string);
		substring->output_string = new_string;
	}
	return ;
}
