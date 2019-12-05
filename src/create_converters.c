/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/05 16:11:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

char			conv_character(va_list *ap)
{
	return ((char)va_arg(*ap, int));
}

t_converter		**create_converters()
{
	t_converter		**converter_array;
	t_converter		*converter;

	converter_array = (t_converter **)ft_memalloc(sizeof(*converter_array) *
			NUM_OF_CONVERTERS);
	converter = (t_converter *)ft_memalloc(sizeof(*converter));
	converter->character = 'c';
	converter->function = conv_character;
	converter_array[0] = converter;
	return (converter_array);
}
