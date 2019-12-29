/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:33:06 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 17:44:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		adjust_character(t_substring *substring)
{
	char		*new_string;

	if ((int)ft_strlen(substring->output_string) < substring->width)
	{
		new_string = modify_substring(substring);
		ft_strdel(&substring->output_string);
		substring->output_string = new_string;
	}
	return ;
}

char		*conv_character(va_list *ap, t_substring *substring,
															int *attrs)
{
	char			*s;
	char			*output_string;

	(*attrs)++;
	s = ft_strnew(1);
	s[0] = (char)va_arg(*ap, void *);
	if (!s[0])
	{
		s[0] = 0x01;
		substring->o_string.add_null = 1;
	}
	output_string = format_string(s, substring);
	return (output_string);
}
