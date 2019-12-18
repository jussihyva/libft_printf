/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:55:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/18 19:08:53 by jkauppi          ###   ########.fr       */
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

static size_t	print_formatted_string(t_list **substring_list)
{
	t_list			*substring_elem;
	t_substring		*substring;
	size_t			words;

	words = 0;
	substring_elem = *substring_list;
	while (substring_elem)
	{
		substring = (t_substring *)(substring_elem->content);
		if (substring->output_string)
			ft_putstr(substring->output_string);
			words += ft_strlen(substring->output_string);
		substring_elem = substring_elem->next;
	}
	return (words);
}

static void		release_memory(t_list **substring_list, t_list **converter_list,
									t_list **formatter_list)
{
	ft_lstdel(substring_list, *del_substring);
	free(substring_list);
	substring_list = NULL;
	ft_lstdel(converter_list, *del_converter);
	free(converter_list);
	converter_list = NULL;
	ft_lstdel(formatter_list, *del_formatter);
	free(formatter_list);
	formatter_list = NULL;
	return ;
}

static int		create_output_string(va_list *ap, const char *format)
{
	size_t			attrs;
	t_list			**substring_list;
	t_list			**converter_list;
	t_list			**formatter_list;
	t_list			**type_list;

	attrs = 0;
	formatter_list = create_formatters();
	converter_list = create_converters();
	type_list = create_param_type_list();
	substring_list = split_string((char *)format, converter_list);
	add_param_type(substring_list, type_list);
	add_width_and_prediction(substring_list);
	attrs = convert_substrings(substring_list, ap, converter_list,
														formatter_list);
	attrs = print_formatted_string(substring_list);
	release_memory(substring_list, converter_list, formatter_list);
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
