/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output_substring_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:11:00 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/30 17:52:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		save_parameter(t_substring *substring, char *s)
{
	substring->o_string.parameter.content = s;
	substring->o_string.parameter.content_size = ft_strlen(s);
}

void			set_prefix(t_substring *substring)
{
	if (substring->flags & hash)
	{
		substring->o_string.prefix.content_size = 1;
		substring->o_string.prefix.content = ft_strdup("0");
	}
	return ;
}
