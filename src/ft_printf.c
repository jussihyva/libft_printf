/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:55:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/11 17:45:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		del_substring(void *substring_elem, size_t size)
{
	t_substring		*elem;

	(void)size;
	elem = (t_substring *)substring_elem;
	ft_strdel(&elem->input_string);
	ft_strdel(&elem->output_string);
	free(substring_elem);
	substring_elem = NULL;
	return ;
}

static void		del_converter(void *converter, size_t size)
{
	(void)size;
	free(converter);
	converter = NULL;
	return ;
}

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
	t_list			**formatter_list;
	int				attrs;

	attrs = 0;
	formatter_list = create_formatters();
	converter_list = create_converters();
	list = split_string((char *)format, converter_list);
	va_start(ap, format);
	attrs = convert_substrings(list, &ap, converter_list, formatter_list);
	va_end(ap);
	print_formatted_string(list);
	ft_lstdel(list, *del_substring);
	ft_lstdel(converter_list, *del_converter);
	free(converter_list);
	converter_list = NULL;
	free(list);
	list = NULL;
	return (attrs);
}
