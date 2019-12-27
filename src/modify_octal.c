/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:46:22 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 14:03:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					adjust_unsigned_octal(t_substring *substring)
{
	char	*new_string;
	char	*pre_string;
	int		offset;

	offset = 0;
	if (substring->flags & hash && substring->output_string[1] == '0')
	{
		if (substring->precision != -1)
			substring->precision++;
		pre_string = ft_strnew(1);
		*pre_string = substring->output_string[0];
		offset = 1;
	}
	else
		pre_string = ft_strnew(0);
	if (substring->precision == offset &&
									substring->output_string[offset] == '0')
		substring->output_string[offset] = '\0';
	if ((int)ft_strlen(substring->output_string) < substring->precision)
		add_min_mum_of_digits(substring, pre_string);
	if ((int)ft_strlen(substring->output_string) < substring->width)
		add_min_mum_of_chars(substring, pre_string);
	if (substring->output_string[0] == '\0' && substring->precision == -1)
	{
		new_string = ft_strnew(1);
		*new_string = '0';
		ft_strdel(&substring->output_string);
		substring->output_string = new_string;
	}
	ft_strdel(&pre_string);
	return ;
}

char					*conv_unsigned_octal(va_list *ap,
										t_substring *substring, int *attrs)
{
	unsigned long long		nbr;
	char					*s;
	char					*output_string;

	(*attrs)++;
	if (!substring->param_type)
		nbr = (unsigned int)(va_arg(*ap, void *));
	else
		nbr = read_o_u_x_param(substring->param_type->type, ap);
	s = ft_ulltoa_base(nbr, 8);
//	if (!nbr)
//		*s = '\0';
	output_string = format_string(s, substring);
	return (output_string);
}
