/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output_substring_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:11:00 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 13:41:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			save_parameter(t_substring *substring, char *s)
{
	substring->o_string.parameter.content = s;
	substring->o_string.parameter.content_size = ft_strlen(s);
	substring->o_string.parameter.next = NULL;
}

void			set_prefix(t_substring *substring)
{
	if (substring->flags & hash && 
					((char *)(substring->o_string.parameter.content))[0] != '0')
	{
		if (substring->conv_type == 'o')
		{
			substring->o_string.prefix.content_size = 1;
			substring->o_string.prefix.content = ft_strdup("0");
		}
		else if (substring->conv_type == 'x' && ((char *)(substring->o_string.parameter.content))[0] != '\0')
		{
			substring->o_string.prefix.content_size = 2;
			substring->o_string.prefix.content = ft_strdup("0x");
		}
		else if (substring->conv_type == 'X' && ((char *)(substring->o_string.parameter.content))[0] != '\0')
		{
			substring->o_string.prefix.content_size = 2;
			substring->o_string.prefix.content = ft_strdup("0X");
		}
	}
	else if (substring->conv_type == 'p')
	{
		substring->o_string.prefix.content_size = 2;
		substring->o_string.prefix.content = ft_strdup("0x");
	}
	return ;
}
