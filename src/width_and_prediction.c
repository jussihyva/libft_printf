/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_prediction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:16:14 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 14:35:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			set_pre_filler(t_substring *substring)
{
	int			num_of_fillers;
	char		*s;

	if (substring->width == -1 || substring->flags & minus)
		num_of_fillers = 0;
	else
	{
		num_of_fillers = substring->width -
						substring->o_string.parameter.content_size -
						substring->o_string.zero_filler.content_size -
						substring->o_string.sign.content_size;
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
		num_of_fillers = substring->width -
						substring->o_string.parameter.content_size -
						substring->o_string.zero_filler.content_size -
						substring->o_string.sign.content_size;
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
	size_t		max_len;

	if (substring->flags & zero &&
					(substring->precision != -1 || substring->width != -1))
	{
		if (substring->precision != -1)
			max_len = substring->precision;
		else
			max_len = substring->width;
		num_of_fillers = max_len -
						substring->o_string.parameter.content_size -
						substring->o_string.zero_filler.content_size -
						substring->o_string.sign.content_size;
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
