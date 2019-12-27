/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:41:12 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 09:41:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				adjust_unsigned_hex(t_substring *substring)
{
	char	*pre_string;

	if (substring->output_string[1] == 'x' ||
		substring->output_string[1] == 'X')
	{
		if (substring->precision != -1)
			substring->precision += 2;
		pre_string = ft_strnew(2);
		*pre_string = substring->output_string[0];
		*(pre_string + 1) = substring->output_string[1];
	}
	else
	{
		if (substring->precision == 0 && substring->output_string[0] == '0')
			substring->output_string[0] = '\0';
		pre_string = ft_strnew(0);
	}
	if ((int)ft_strlen(substring->output_string) < substring->precision)
		add_min_mum_of_digits(substring, pre_string);
	if ((int)ft_strlen(substring->output_string) < substring->width)
		add_min_mum_of_chars(substring, pre_string);
	ft_strdel(&pre_string);
	return ;
}

char				*conv_unsigned_hex(va_list *ap, t_substring *substring,
																int *attrs)
{
	unsigned long long		nbr;
	char					*s;
	char					*output_string;

	(*attrs)++;
	if (!substring->param_type)
		nbr = (unsigned int)(va_arg(*ap, void *));
	else
		nbr = read_o_u_x_param(substring->param_type->type, ap);
	s = ft_ulltoa_base(nbr, 16);
	output_string = format_string(s, substring);
	return (output_string);
}

char				*conv_unsigned_hex_up(va_list *ap,
										t_substring *substring, int *attrs)
{
	unsigned long long		nbr;
	char					*s;
	char					*output_string;
	int						i;

	(*attrs)++;
	if (!substring->param_type)
		nbr = (unsigned int)(va_arg(*ap, void *));
	else
		nbr = read_o_u_x_param(substring->param_type->type, ap);
	s = ft_ulltoa_base(nbr, 16);
	output_string = format_string(s, substring);
	i = -1;
	while (*(output_string + ++i))
		*(output_string + i) = ft_toupper(*(output_string + i));
	return (output_string);
}