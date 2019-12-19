/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 09:30:35 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/19 12:18:57 by jkauppi          ###   ########.fr       */
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
		string_len = ft_strlen(string);
		ft_strcat(new_string, pre_string);
		ft_memset(new_string + offset, filler, width - string_len);
		ft_strcat(new_string + width - string_len, string + offset);
		ft_strdel(&string);
	}
	return (new_string);
}
