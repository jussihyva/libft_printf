/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 09:30:35 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/22 19:51:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
