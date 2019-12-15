/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:55:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/15 18:55:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		del_formatter(void *formatter, size_t size)
{
	(void)size;
	free(formatter);
	formatter = NULL;
	return ;
}

static void		del_substring(void *substring_elem, size_t size)
{
	t_substring		*elem;

	(void)size;
	elem = (t_substring *)substring_elem;
	ft_strdel(&elem->input_string);
	ft_strdel(&elem->output_string);
	if (elem->formatter_list)
	{
		ft_lstdel(elem->formatter_list, *del_formatter);
		free(elem->formatter_list);
		elem->formatter_list = NULL;
	}
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

static int		create_output_string(va_list *ap, const char *format)
{
	int				attrs;
	t_list			**list;
	t_list			**converter_list;
	t_list			**formatter_list;
	t_list			**type_list;

	attrs = 0;
	formatter_list = create_formatters();
	converter_list = create_converters();
	type_list = create_param_type_list();
	list = split_string((char *)format, converter_list);
	add_param_type(list, type_list);
	attrs = convert_substrings(list, ap, converter_list, formatter_list);
	print_formatted_string(list);
	ft_lstdel(list, *del_substring);
	free(list);
	list = NULL;
	ft_lstdel(converter_list, *del_converter);
	free(converter_list);
	converter_list = NULL;
	ft_lstdel(formatter_list, *del_formatter);
	free(formatter_list);
	formatter_list = NULL;
	return (attrs);
}

int				ft_printf(const char *restrict format, ...)
{
	va_list			ap;
	int				attrs;

	va_start(ap, format);
	attrs = create_output_string(&ap, format);
	va_end(ap);
	return (attrs);
}
