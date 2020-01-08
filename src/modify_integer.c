/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:24:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/08 17:08:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_int_parameter(t_substring *substring)
{
	char			*s;
	long long		par_value;

	par_value = *(long long *)substring->par_value;
	s = ft_lltoa_base(par_value, 10);
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

void						adjust_int(t_substring *substring)
{
	char	*pre_string;
	int		offset;

	set_int_parameter(substring);
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
	offset = 0;
	if (substring->output_string[0] == '+' ||
		substring->output_string[0] == '-' ||
		substring->output_string[0] == ' ')
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
	ft_strdel(&pre_string);
	return ;
}

void						adjust_unsigned_int(t_substring *substring)
{
	char	*pre_string;

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

char						*conv_int(va_list *ap, t_substring *substring,
											int *attrs)
{
	long long		*nbr;

	(*attrs)++;
	nbr = (long long *)ft_memalloc(sizeof(*nbr));
	if (!substring->param_type)
		*nbr = (int)(va_arg(*ap, void *));
	else
		*nbr = read_int_param(substring->param_type->type, ap);
	substring->par_value = nbr;
	if (*nbr < 0)
		substring->par_value_is_neg = 1;
	format_string(ft_strnew(0), substring);
	return (NULL);
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
		nbr = read_o_u_x_param(substring->param_type->type, ap);
	s = ft_ulltoa_base(nbr, 10);
	if (s[0] == '-')
		output_string = format_string(s + 1, substring);
	else
		output_string = format_string(s, substring);
	return (output_string);
}
