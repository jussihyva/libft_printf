/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_prediction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:16:14 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/18 12:51:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*modify_substring(t_substring *substring)
{
	char		*new_string;

	new_string = ft_strnew(sizeof(*new_string) * (substring->width));
	if (substring->left_adjust)
	{
		ft_strcat(new_string, substring->output_string);
		ft_memset(new_string + ft_strlen(substring->output_string),
									' ', substring->width -
									ft_strlen(substring->output_string));
	}
	else
	{
		ft_memset(new_string, substring->filler, substring->width -
									ft_strlen(substring->output_string));
		ft_strcat(new_string, substring->output_string);
	}
	return (new_string);
}

void			width_adjust(t_substring *substring)
{
	if (substring->converter)
		substring->converter->adjust_width_prediction_ptr(substring);
	return ;
}

static void		save_width_and_prediction(char **ptr,
												t_list *substring_elem)
{
	if (**ptr == '.')
	{
		((t_substring *)substring_elem->content)->precision =
													ft_atoi(*ptr + 1);
		(*ptr)--;
		while (**ptr && ft_isdigit(**ptr))
			(*ptr)--;
		((t_substring *)substring_elem->content)->width =
													ft_atoi(*ptr + 1);
	}
	else
	{
		((t_substring *)substring_elem->content)->precision = -1;
		((t_substring *)substring_elem->content)->width =
													ft_atoi(*ptr + 1);
	}
	if (*(*ptr + 1) == '0')
		(*ptr)++;
	return ;
}

void			add_width_and_prediction(t_list **substring_list)
{
	t_list			*substring_elem;
	char			*ptr;

	substring_elem = *substring_list;
	while (substring_elem)
	{
		ptr = ((t_substring *)substring_elem->content)->end_ptr;
		while (*ptr && (ft_isdigit(*ptr)))
			ptr--;
		if (*ptr == '.' ||
					ptr < ((t_substring *)substring_elem->content)->end_ptr)
		{
			save_width_and_prediction(&ptr, substring_elem);
		}
		((t_substring *)substring_elem->content)->end_ptr = ptr;
		substring_elem = substring_elem->next;
	}
	return ;
}
