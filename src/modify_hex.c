/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:41:12 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/23 08:50:16 by jkauppi          ###   ########.fr       */
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

static long long	read_hex_param(t_type type, va_list *ap)
{
	long long	nbr;

	if (type == hh)
		nbr = (unsigned char)(va_arg(*ap, void *));
	else if (type == h)
		nbr = (unsigned short)(va_arg(*ap, void *));
	else if (type == l)
		nbr = (unsigned long)(va_arg(*ap, void *));
	else if (type == ll)
		nbr = (unsigned long long)(va_arg(*ap, void *));
	else if (type == j)
		nbr = (uintmax_t)(va_arg(*ap, void *));
	else if (type == z)
		nbr = (size_t)(va_arg(*ap, void *));
	else if (type == t)
		nbr = (ptrdiff_t)(va_arg(*ap, void *));
	else if (type == L)
		nbr = (unsigned char)(va_arg(*ap, void *));
	else
		nbr = (unsigned char)(va_arg(*ap, void *));
	return (nbr);
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
		nbr = read_hex_param(substring->param_type->type, ap);
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
		nbr = read_hex_param(substring->param_type->type, ap);
	s = ft_ulltoa_base(nbr, 16);
	output_string = format_string(s, substring);
	i = -1;
	while (*(output_string + ++i))
		*(output_string + i) = ft_toupper(*(output_string + i));
	return (output_string);
}
