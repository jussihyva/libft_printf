/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:58:22 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 13:03:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		adjust_pointer(t_substring *substring)
{
	char	*pre_string;
	int		offset;

	offset = 0;
	if (substring->output_string[1] == 'x' ||
		substring->output_string[1] == 'X')
	{
		if (substring->precision != -1)
			substring->precision += 2;
		pre_string = ft_strnew(2);
		*pre_string = substring->output_string[0];
		*(pre_string + 1) = substring->output_string[1];
		offset = 2;
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

char		*conv_pointer(va_list *ap, t_substring *substring, int *attrs)
{
	uintptr_t		ptr;
	char			*ptr_string;
	char			*s;
	char			*output_string;

	(*attrs)++;
	ptr = (uintptr_t)(va_arg(*ap, void *));
	ptr_string = ft_lltoa_base(ptr, 16);
	s = ft_strjoin("0x", ptr_string);
	ft_strdel(&ptr_string);
	output_string = format_string(s, substring);
	return (output_string);
}
