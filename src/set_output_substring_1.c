/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output_substring_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:52:22 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/08 20:59:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_num_of_fillers(t_substring *substring, int min_len)
{
	int		num_of_fillers;

	num_of_fillers = min_len -
				substring->o_string.parameter.content_size -
				substring->o_string.zero_filler.content_size -
				substring->o_string.prefix.content_size -
				substring->o_string.sign.content_size;
	return (num_of_fillers);
}

static int		count_num_of_zero_fillers(t_substring *substring, int min_len)
{
	int		num_of_fillers;

	if (substring->conv_type == 'd' || substring->conv_type == 'i' ||
		substring->conv_type == 'x' || substring->conv_type == 'X')
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

void			set_pre_filler(t_substring *substring)
{
	int			num_of_fillers;
	char		*s;
	char		filler;

	if (substring->width == -1 || substring->flags & minus)
		num_of_fillers = 0;
	else
	{
		num_of_fillers = count_num_of_fillers(substring, substring->width);
		if (num_of_fillers > 0)
		{
			s = ft_strnew(num_of_fillers);
			*(s + num_of_fillers) = '\0';
			substring->o_string.pre_filler.content_size = num_of_fillers;
			substring->o_string.pre_filler.content = s;
			if (substring->conv_type == 'o' && substring->precision == -1)
				filler = substring->filler;
			else if (substring->conv_type == 'c')
				filler = substring->filler;
			else
				filler = ' ';
			while (num_of_fillers--)
				*(s + num_of_fillers) = filler;
		}
	}
}

void			set_post_filler(t_substring *substring)
{
	int			num_of_fillers;
	char		*s;

	if (substring->width == -1 || !(substring->flags & minus))
		num_of_fillers = 0;
	else
	{
		num_of_fillers = count_num_of_fillers(substring, substring->width);
		if (num_of_fillers > 0)
		{
			s = ft_strnew(num_of_fillers);
			*(s + num_of_fillers) = '\0';
			substring->o_string.post_filler.content_size = num_of_fillers;
			substring->o_string.post_filler.content = s;
			while (num_of_fillers--)
				*(s + num_of_fillers) = ' ';
		}
	}
	return ;
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
	int			num_of_fillers;
	char		filler;

	num_of_fillers = 0;
	filler = substring->filler;
	if (substring->conv_type == 'c')
		;
	else if (substring->conv_type == 'f')
	{
		if (substring->width != -1 && !(substring->flags & minus) &&
				(substring->flags & zero))
			num_of_fillers = count_num_of_fillers(substring, substring->width);
		else if (substring->precision != -1)
		{
			num_of_fillers = count_num_of_zero_fillers(substring, substring->precision);
			filler = '0';
		}
	}
	else if (substring->precision != -1)
	{
		num_of_fillers = count_num_of_zero_fillers(substring, substring->precision);
		filler = '0';
	}
	else if (substring->conv_type == 'd' ||
				substring->conv_type == 'i' ||
				substring->conv_type == 'x' ||
				substring->conv_type == 'X' ||
				substring->conv_type == 'u')
	{
		if (substring->width != -1 && !(substring->flags & minus) &&
			(substring->flags & zero))
			num_of_fillers = count_num_of_fillers(substring, substring->width);
	}
	add_filler(&substring->o_string.zero_filler, num_of_fillers, filler);
	return ;
}

void			set_sign(t_substring *substring)
{
	char		conv_type;

	conv_type = substring->conv_type;
	if (conv_type == 'f' || conv_type == 'd' || conv_type == 'i')
	{
		if (substring->par_value_is_neg)
		{
			substring->o_string.sign.content = ft_strdup("-");
			substring->o_string.sign.content_size = 1;
		}
		else if (substring->flags & plus)
		{
			substring->o_string.sign.content = ft_strdup("+");
			substring->o_string.sign.content_size = 1;
		}
		else if (substring->flags & space)
		{
			substring->o_string.sign.content = ft_strdup(" ");
			substring->o_string.sign.content_size = 1;
		}
	}
}
