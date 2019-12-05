/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/05 16:38:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

static int			conv_character(va_list *ap)
{
	return (va_arg(*ap, int));
}

static char			*conv_string(va_list *ap)
{
	return (va_arg(*ap, char *));
}

t_converter			**create_converters()
{
	t_converter		**converter_array;
	t_converter		*converter;

	converter_array = (t_converter **)ft_memalloc(sizeof(*converter_array) *
			NUM_OF_CONVERTERS);
	converter = (t_converter *)ft_memalloc(sizeof(*converter));
	converter->character = 'c';
	converter->function_ptr = (void *)conv_character;
	converter_array[0] = converter;
	converter = (t_converter *)ft_memalloc(sizeof(*converter));
	converter->character = 's';
	converter->function_ptr = (void *)conv_string;
	converter_array[1] = converter;
	return (converter_array);
}
