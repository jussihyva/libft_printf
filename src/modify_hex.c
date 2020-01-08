/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:41:12 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/08 20:58:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_unsigned_hex_parameter(t_substring *substring)
{
	char					*s;
	unsigned long long		par_value;
	size_t					i;

	par_value = *(unsigned long long *)substring->par_value;
	s = ft_ulltoa_base(par_value, 16);
	if (substring->conv_type == 'X')
	{
		i = -1;
		while (*(s + ++i))
			*(s + i) = ft_toupper(*(s + i));
	}
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

void				adjust_unsigned_hex(t_substring *substring)
{
	char	*pre_string;

	set_unsigned_hex_parameter(substring);
	set_sign(substring);
	set_prefix(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
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
	unsigned long long		*nbr;

	(*attrs)++;
	nbr = (unsigned long long *)ft_memalloc(sizeof(*nbr));
	if (!substring->param_type)
		*nbr = (unsigned int)(va_arg(*ap, void *));
	else
		*nbr = read_o_u_x_param(substring->param_type->type, ap);
	substring->par_value = nbr;
	if (*nbr < 0)
		substring->par_value_is_neg = 1;
	format_string(ft_strnew(0), substring);
	return (NULL);
}
