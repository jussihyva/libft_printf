/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_substring_zero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:21:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/10 10:24:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_zero_fillers(t_substring *substring, int min_len)
{
	int		num_of_fillers;

	if (substring->conv_type == 'd' || substring->conv_type == 'i' ||
		substring->conv_type == 'x' || substring->conv_type == 'X' ||
		substring->conv_type == 'p')
		num_of_fillers = min_len -
						substring->o_string.parameter.content_size -
						substring->o_string.zero_filler.content_size;
	else
		num_of_fillers = min_len -
						substring->o_string.parameter.content_size -
						substring->o_string.zero_filler.content_size -
						substring->o_string.prefix.content_size -
						substring->o_string.sign.content_size;
	return (num_of_fillers);
}

static char		set_zero_filler_char(t_substring *substring)
{
	char		filler;

	filler = ' ';
	if (substring->flags & zero)
		filler = '0';
	if (substring->precision != -1)
		filler = '0';
	return (filler);
}

static void		add_filler(t_list *elem, int num_of_fillers, char filler)
{
	char		*s;

	if (num_of_fillers > 0)
	{
		s = ft_strnew(num_of_fillers);
		*(s + num_of_fillers) = '\0';
		elem->content_size = num_of_fillers;
		elem->content = s;
		while (num_of_fillers--)
			*(s + num_of_fillers) = filler;
	}
	return ;
}

void			set_zero_filler(t_substring *substring)
{
	int			num_fillers;
	char		filler;

	num_fillers = 0;
	filler = set_zero_filler_char(substring);
	if (substring->conv_type == 'c' || substring->conv_type == 's' ||
													substring->conv_type == '%')
		;
	else if (substring->conv_type == 'f')
	{
		if (substring->width != -1 && !(substring->flags & minus) &&
				(substring->flags & zero))
			num_fillers = count_num_of_fillers(substring, substring->width);
		else if (substring->precision != -1)
			num_fillers = count_zero_fillers(substring, substring->precision);
	}
	else if (substring->precision != -1)
		num_fillers = count_zero_fillers(substring, substring->precision);
	else if (ft_strchr("dixXpu", substring->conv_type))
		if (substring->width != -1 && !(substring->flags & minus) &&
			(substring->flags & zero))
			num_fillers = count_num_of_fillers(substring, substring->width);
	add_filler(&substring->o_string.zero_filler, num_fillers, filler);
	return ;
}
