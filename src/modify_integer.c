/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:24:14 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/19 16:35:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				add_min_mum_of_digits(t_substring *substring, char c)
{
	char		*new_string;

	if (c == '@')
		substring->output_string = right_adjust('0',
							substring->output_string, substring->precision, "");
	else
	{
		new_string = ft_strnew(1);
		*new_string = c;
		substring->output_string = right_adjust('0',
				substring->output_string, substring->precision, new_string);
		ft_strdel(&new_string);
	}
	return ;
}

static void				add_min_mum_of_chars(t_substring *substring, char c)
{
	char		*new_string;

	if (substring->left_adjust)
		substring->output_string = left_adjust(substring->output_string,
												substring->width);
	else
	{
		if (substring->filler == ' ' || substring->precision != -1)
			substring->output_string = right_adjust(' ',
							substring->output_string, substring->width, "");
		else
		{
			if (c == '@')
				substring->output_string = right_adjust(substring->filler,
							substring->output_string, substring->width, "");
			else
			{
				new_string = ft_strnew(1);
				*new_string = c;
				substring->output_string = right_adjust('0',
						substring->output_string, substring->width, new_string);
				ft_strdel(&new_string);
			}
		}
	}
}

void					adjust_int(t_substring *substring)
{
	if (substring->output_string[0] == '+' ||
		substring->output_string[0] == '-' ||
		substring->output_string[0] == ' ')
	{
		if (substring->precision != -1)
			substring->precision++;
		if ((int)ft_strlen(substring->output_string) < substring->precision)
			add_min_mum_of_digits(substring, substring->output_string[0]);
		if ((int)ft_strlen(substring->output_string) < substring->width)
			add_min_mum_of_chars(substring, substring->output_string[0]);
	}
	else
	{
		if ((int)ft_strlen(substring->output_string) < substring->precision)
			add_min_mum_of_digits(substring, '@');
		if ((int)ft_strlen(substring->output_string) < substring->width)
			add_min_mum_of_chars(substring, '@');
	}
	return ;
}

void					adjust_unsigned_int(t_substring *substring)
{
	if (substring->output_string[0] ==  ' ')
	{
		if ((int)ft_strlen(substring->output_string) < substring->precision + 1)
			add_min_mum_of_digits(substring, substring->output_string[0]);
		if ((int)ft_strlen(substring->output_string) < substring->width)
			add_min_mum_of_chars(substring, substring->output_string[0]);
	}
	else
	{
		if ((int)ft_strlen(substring->output_string) < substring->precision)
			add_min_mum_of_digits(substring, '@');
		if ((int)ft_strlen(substring->output_string) < substring->width)
			add_min_mum_of_chars(substring, '@');
	}
	return ;
}

static unsigned long	read_int_param(t_type type, va_list *ap)
{
	unsigned long	nbr;

	if (type == hh)
		nbr = (char)(va_arg(*ap, void *));
	else if (type == h)
		nbr = (short int)(va_arg(*ap, void *));
	else if (type == l)
		nbr = (long int)(va_arg(*ap, void *));
	else if (type == ll)
		nbr = (long long int)(va_arg(*ap, void *));
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

char					*conv_int(va_list *ap, t_substring *substring,
											int *attrs)
{
	unsigned long	nbr;
	char			*s;
	char			*output_string;

	(*attrs)++;
	if (!substring->param_type)
		nbr = (int)(va_arg(*ap, void *));
	else
		nbr = read_int_param(substring->param_type->type, ap);
	s = ft_ltoa_base(nbr, 10);
	output_string = format_string(s, substring);
	return (output_string);
}

char					*conv_unsigned_int(va_list *ap, t_substring *substring,
															int *attrs)
{
	unsigned int	nbr;
	char			*s;
	char			*output_string;

	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 10);
	output_string = format_string(s, substring);
	return (output_string);
}
