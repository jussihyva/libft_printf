/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:55:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/08 12:29:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_formatted_string(t_list **list)
{
	t_list			*elem;
	t_substring		*substring;

	elem = *list;
	while (elem)
	{
		substring = (t_substring *)(elem->content);
		if (substring->output_string)
			ft_putstr(substring->output_string);
		elem = elem->next;
	}
	ft_putchar('\n');
}

int				ft_printf(const char *restrict format, ...)
{
	va_list			ap;
	t_list			**list;
	t_list			**converter_list;
	int				attrs;

	converter_list = create_converters();
	list = split_string((char *)format, converter_list);
	va_start(ap, format);
	attrs = convert_substrings(list, &ap, converter_list);
	va_end(ap);
	print_formatted_string(list);
	return (attrs);
}
