/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:46:22 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 16:48:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					special_adjust(t_substring *substring)
{
	char	*new_string;

	if (substring->output_string[0] == '\0' && substring->precision == -1)
	{
		new_string = ft_strnew(1);
		*new_string = '0';
		ft_strdel(&substring->output_string);
		substring->output_string = new_string;
	}
	return ;
}

void					adjust_unsigned_octal(t_substring *substring)
{
	char	*pre_string;
	int		offset;

	offset = 0;
	if (substring->flags & hash)
	{
		pre_string = ft_strnew(1);
		offset = 1;
		*pre_string = substring->output_string[0];
		if (substring->output_string[1] == '0')
		{
			if (substring->precision != -1)
				substring->precision++;
			if (substring->output_string[offset] == '0')
				substring->output_string[offset] = '\0';
		}
	}
	else
		pre_string = ft_strnew(0);
	adjust_common(substring, offset, pre_string);
	special_adjust(substring);
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
	output_string = format_string(s, substring);
	return (output_string);
}
