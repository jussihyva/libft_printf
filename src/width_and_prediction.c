/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_prediction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:16:14 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/16 13:20:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				add_width_and_prediction(t_list **substring_list)
{
	t_list			*substring_elem;

	substring_elem = *substring_list;
	while (substring_elem)
	{
		substring_elem = substring_elem->next;
	}
	return ;
}
