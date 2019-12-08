/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:55:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/08 11:50:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *restrict format, ...)
{
	int				attrs;
	va_list			ap;
	char			*input_string;
	t_list			**list;
	t_list			*elem;
	int				max_num_attrs;
	t_list			**converter_list;
	t_substring		*substring;

	converter_list = create_converters();
	max_num_attrs = 190;
	attrs = 0;
	input_string = (char *)format;
	list = split_string(input_string, converter_list);
	va_start(ap, format);
	elem = *list;
	while (elem)
	{
		substring = (t_substring *)(elem->content);
		add_converter(substring, converter_list);
		convert_substring(substring, &ap);
		ft_putstr(substring->input_string);
		ft_putstr("  ");
		if (substring->converter)
			ft_putchar((substring->converter)->character);
		else
			ft_putstr("null");
		ft_putchar('\n');
		elem = elem->next;
	}
	elem = *list;
	while (elem)
	{
		substring = (t_substring *)(elem->content);
		if (substring->output_string)
			ft_putstr(substring->output_string);
		elem = elem->next;
	}
	ft_putchar('\n');
	va_end(ap);
	return (attrs);
}
