/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 09:30:35 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 16:45:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		read_o_u_x_param(t_type type, va_list *ap)
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

char			*left_adjust(char *string, size_t width)
{
	char		*new_string;
	size_t		string_len;

	if ((new_string = ft_strnew(sizeof(*new_string) * width)))
	{
		ft_strcat(new_string, string);
		string_len = ft_strlen(string);
		ft_memset(new_string + string_len, ' ', width - string_len);
		ft_strdel(&string);
	}
	return (new_string);
}

char			*right_adjust(char filler, char *string, size_t width,
														char *pre_string)
{
	char		*new_string;
	size_t		string_len;
	size_t		offset;

	if ((new_string = ft_strnew(sizeof(*new_string) * width)))
	{
		offset = ft_strlen(pre_string);
		string_len = ft_strlen(string + offset);
		ft_strcat(new_string, pre_string);
		ft_memset(new_string + offset, filler, width - string_len - offset);
		ft_strcat(new_string + width - string_len - offset, string + offset);
		ft_strdel(&string);
	}
	return (new_string);
}

void			add_min_mum_of_digits(t_substring *substring, char *pre_string)
{
	substring->output_string = right_adjust('0',
				substring->output_string, substring->precision, pre_string);
	return ;
}

void			add_min_mum_of_chars(t_substring *substring, char *pre_string)
{
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
			if (pre_string)
				substring->output_string = right_adjust('0',
						substring->output_string, substring->width, pre_string);
			else
				substring->output_string = right_adjust(substring->filler,
						substring->output_string, substring->width, "");
		}
	}
	return ;
}

void			adjust_common(t_substring *substring, int offset,
														char *pre_string)
{
	if (substring->precision == offset &&
									substring->output_string[offset] == '0')
		substring->output_string[offset] = '\0';
	if ((int)ft_strlen(substring->output_string) < substring->precision)
		add_min_mum_of_digits(substring, pre_string);
	if ((int)ft_strlen(substring->output_string) < substring->width)
		add_min_mum_of_chars(substring, pre_string);
}
