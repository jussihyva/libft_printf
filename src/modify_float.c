/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:01:45 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 18:04:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*conv_float(va_list *ap, t_substring *substring,
															int *attrs)
{
	unsigned long	tmp;
	double			nbr;
	char			*s;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	tmp = (unsigned long)va_arg(*ap, void *);
	nbr = (double)tmp;
	nbr *= 1000000;
	s = ft_lltoa_base(nbr, 10);
	return (s);
}

void					adjust_float(t_substring *substring)
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
