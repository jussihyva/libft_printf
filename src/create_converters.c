/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/07 12:12:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			conv_character(va_list *ap)
{
	return (va_arg(*ap, int));
}

static char			*conv_string(va_list *ap)
{
	return (va_arg(*ap, char *));
}

static t_converter	*create_converter(void *function, char character)
{
	t_converter		*converter;

	converter = (t_converter *)ft_memalloc(sizeof(*converter));
	converter->character = character;
	converter->function_ptr = function;
	return (converter);
}

t_converter			**create_converters(void)
{
	t_converter		**converter_array;

	converter_array = (t_converter **)ft_memalloc(sizeof(*converter_array) *
			NUM_OF_CONVERTERS);
	converter_array[0] = create_converter((void *)conv_character, '%');
	converter_array[1] = create_converter((void *)conv_character, 'c');
	converter_array[2] = create_converter((void *)conv_string, 's');
	converter_array[3] = create_converter((void *)conv_string, 'p');
	return (converter_array);
}
