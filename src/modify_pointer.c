/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:58:22 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/18 17:33:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	add_min_mum_of_digits(t_substring *substring)
{
	char		*new_string;

	new_string = ft_strnew(sizeof(*new_string) * (substring->precision + 2));
	*new_string = '\0';
	ft_strcat(new_string, "0x");
	ft_memset(new_string + 2, '0', substring->precision -
									ft_strlen(substring->output_string) + 2);
	ft_strcat(new_string, substring->output_string + 2);
	ft_strdel(&substring->output_string);
	substring->output_string = new_string;
	return ;
}

static void	add_min_mum_of_chars(t_substring *substring)
{
	char		*new_string;

	new_string = ft_strnew(sizeof(*new_string) * (substring->width));
	*new_string = '\0';
	if (substring->filler == ' ' || substring->precision != -1)
	{
		ft_memset(new_string, ' ', substring->width -
									ft_strlen(substring->output_string));
		ft_strcat(new_string, substring->output_string);
	}
	else
	{
		ft_strcat(new_string, "0x");
		ft_memset(new_string + 2, substring->filler, substring->width -
									ft_strlen(substring->output_string));
		ft_strcat(new_string, substring->output_string + 2);
	}
	ft_strdel(&substring->output_string);
	substring->output_string = new_string;
	return ;
}

void		adjust_pointer(t_substring *substring)
{
	if (substring->precision == 0 && substring->output_string[2] == '0' &&
			ft_strlen(substring->output_string) == 3)
		substring->output_string[2] = '\0';
	if ((int)ft_strlen(substring->output_string + 2) < substring->precision)
	{
		add_min_mum_of_digits(substring);
	}
	if ((int)ft_strlen(substring->output_string) < substring->width)
	{
		add_min_mum_of_chars(substring);
	}
	return ;
}

char		*conv_pointer(va_list *ap, t_substring *substring, int *attrs)
{
	uintptr_t		ptr;
	char			*ptr_string;
	char			*s;
	char			*output_string;

	(*attrs)++;
	ptr = (uintptr_t)(va_arg(*ap, void *));
	ptr_string = ft_ltoa_base(ptr, 16);
	s = ft_strjoin("0x", ptr_string);
	ft_strdel(&ptr_string);
	output_string = format_string(s, substring);
	return (output_string);
}
