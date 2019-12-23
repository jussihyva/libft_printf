/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:53:59 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/23 09:23:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		adjust_string(t_substring *substring)
{
	char		*new_string;

	if (substring->precision >= 0)
	{
		if ((int)ft_strlen(substring->output_string) > substring->precision)
			substring->output_string[substring->precision] = '\0';
	}
	if ((int)ft_strlen(substring->output_string) < substring->width)
	{
		new_string = modify_substring(substring);
		ft_strdel(&substring->output_string);
		substring->output_string = new_string;
	}
	return ;
}

char		*conv_string(va_list *ap, t_substring *substring, int *attrs)
{
	char			*s;
	char			*output_string;

	(*attrs)++;
	s = ft_strdup((char *)va_arg(*ap, void *));
	if (!s)
		s = ft_strdup("(null)");
	output_string = format_string(s, substring);
	return (output_string);
}

char		*conv_percent_char(va_list *ap, t_substring *substring, int *attrs)
{
	char			*s;
	char			*output_string;

	(void)ap;
	(void)attrs;
	s = ft_strdup(substring->input_string);
	s[ft_strlen(s) - 1] = '\0';
	output_string = format_string(s, substring);
	return (output_string);
}
