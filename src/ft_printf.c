/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:55:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/07 12:13:46 by jkauppi          ###   ########.fr       */
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
	t_converter		**converter_array;
	int				tmp1;
//	char			*tmp2;

	converter_array = create_converters();
	max_num_attrs = 190;
	attrs = 0;
	input_string = (char *)format;
	list = split_input_string(input_string, converter_array);
	elem = *list;
	while (elem)
	{
		ft_putstr(((t_substring *)(elem->content))->input_string);
		ft_putchar('\n');
		elem = elem->next;
	}
	va_start(ap, format);
	tmp1 = (int)converter_array[0]->function_ptr(&ap);
	ft_putchar(tmp1);
//	tmp2 = (char *)converter_array[1]->function_ptr(&ap);
//	ft_putstr(tmp2);
/*
	while (*format && attrs <= max_num_attrs)
	{
		attrs++;
		nbr = (int)va_arg(ap, int *);
		ft_putnbr(chars);
		ft_putchar(' ');
		ft_putnbr(nbr);
		ft_putchar('\n');
	}
*/
	va_end(ap);
	return (attrs);
}
