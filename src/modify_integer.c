/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:24:14 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/26 09:47:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						adjust_int(t_substring *substring)
{
	char	*pre_string;

	if (substring->output_string[0] == '+' ||
		substring->output_string[0] == '-' ||
		substring->output_string[0] == ' ')
	{
		if (substring->precision != -1)
			substring->precision++;
		pre_string = ft_strnew(1);
		*pre_string = substring->output_string[0];
	}
	else
		pre_string = ft_strnew(0);
	if (substring->precision == 0 && substring->output_string[0] == '0')
		substring->output_string[substring->precision] = '\0';
	if ((int)ft_strlen(substring->output_string) < substring->precision)
		add_min_mum_of_digits(substring, pre_string);
	if ((int)ft_strlen(substring->output_string) < substring->width)
		add_min_mum_of_chars(substring, pre_string);
	ft_strdel(&pre_string);
	return ;
}

void						adjust_unsigned_int(t_substring *substring)
{
	char	*pre_string;

	pre_string = ft_strnew(0);
	if ((int)ft_strlen(substring->output_string) < substring->precision)
		add_min_mum_of_digits(substring, pre_string);
	if ((int)ft_strlen(substring->output_string) < substring->width)
		add_min_mum_of_chars(substring, pre_string);
	ft_strdel(&pre_string);
	return ;
}

static long long			read_int_param(t_type type, va_list *ap)
{
	long long	nbr;

	if (type == hh)
		nbr = (char)(va_arg(*ap, void *));
	else if (type == h)
		nbr = (short)(va_arg(*ap, void *));
	else if (type == l)
		nbr = (long)(va_arg(*ap, void *));
	else if (type == ll)
		nbr = (long long)(va_arg(*ap, void *));
	else if (type == j)
		nbr = (intmax_t)(va_arg(*ap, void *));
	else if (type == z)
		nbr = (size_t)(va_arg(*ap, void *));
	else if (type == t)
		nbr = (ptrdiff_t)(va_arg(*ap, void *));
	else if (type == L)
		nbr = (int)(va_arg(*ap, void *));
	else
		nbr = (int)(va_arg(*ap, void *));
	return (nbr);
}

static long long			read_un_int_param(t_type type, va_list *ap)
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

char						*conv_int(va_list *ap, t_substring *substring,
											int *attrs)
{
	long long		nbr;
	char			*s;
	char			*output_string;

	(*attrs)++;
	if (!substring->param_type)
		nbr = (int)(va_arg(*ap, void *));
	else
		nbr = read_int_param(substring->param_type->type, ap);
	s = ft_lltoa_base(nbr, 10);
	output_string = format_string(s, substring);
	return (output_string);
}

char						*conv_unsigned_int(va_list *ap,
										t_substring *substring, int *attrs)
{
	unsigned long long		nbr;
	char					*s;
	char					*output_string;

	(*attrs)++;
	if (!substring->param_type)
		nbr = (unsigned int)(va_arg(*ap, void *));
	else
		nbr = read_un_int_param(substring->param_type->type, ap);
	s = ft_ulltoa_base(nbr, 10);
	if (s[0] == '-')
		output_string = format_string(s + 1, substring);
	else
		output_string = format_string(s, substring);
	return (output_string);
}
