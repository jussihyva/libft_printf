/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:52:22 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 18:13:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_num_of_fillers(t_substring *substring, int min_len)
{
	int		num_of_fillers;

	num_of_fillers = min_len -
						substring->o_string.parameter.content_size -
						substring->o_string.zero_filler.content_size -
						substring->o_string.sign.content_size;
	return (num_of_fillers);
}

void			set_pre_filler(t_substring *substring)
{
	int			num_of_fillers;
	char		*s;

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
			while (num_of_fillers--)
				*(s + num_of_fillers) = substring->filler;
		}
	}
	return ;
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
				*(s + num_of_fillers) = substring->filler;
		}
	}
	return ;
}

void			set_zero_filler(t_substring *substring)
{
	int			num_of_fillers;
	char		*s;

	if (substring->flags & zero &&
					(substring->precision != -1 || substring->width != -1))
	{
		if (substring->width != -1)
			num_of_fillers = count_num_of_fillers(substring, substring->width);
		else
			num_of_fillers =
						count_num_of_fillers(substring, substring->precision);
		if (num_of_fillers > 0)
		{
			s = ft_strnew(num_of_fillers);
			*(s + num_of_fillers) = '\0';
			substring->o_string.zero_filler.content_size = num_of_fillers;
			substring->o_string.zero_filler.content = s;
			while (num_of_fillers--)
				*(s + num_of_fillers) = '0';
		}
	}
	else
		num_of_fillers = 0;
	return ;
}

void			set_sign(t_substring *substring)
{
	if (substring->flags & plus)
	{
		if (((char *)substring->o_string.parameter.content)[0] != '-')
		{
			substring->o_string.sign.content = ft_strdup("+");
			substring->o_string.sign.content_size = 1;
		}
	}
	else if (substring->flags & space)
	{
		if (((char *)substring->o_string.parameter.content)[0] != '-')
		{
			substring->o_string.sign.content = ft_strdup(" ");
			substring->o_string.sign.content_size = 1;
		}
	}
}
