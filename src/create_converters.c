/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/07 14:00:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				add_converter(t_substring *substring,
							t_converter **converter_list)
{
	char			character;
	char			*input_string;
	int				i;

	input_string = substring->input_string;
	character = input_string[ft_strlen(input_string) - 1];
	i = -1;
	substring->converter = NULL;
	while (++i < NUM_OF_CONVERTERS)
	{
		if (character == converter_list[i]->character)
			substring->converter = converter_list[i];
	}
}

static void			no_conv(va_list *ap)
{
	(void)ap;
	return ;
}

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
	t_converter		**converter_list;

	converter_list = (t_converter **)ft_memalloc(sizeof(*converter_list) *
			NUM_OF_CONVERTERS);
	converter_list[0] = create_converter((void *)no_conv, '%');
	converter_list[1] = create_converter((void *)conv_character, 'c');
	converter_list[2] = create_converter((void *)conv_string, 's');
	converter_list[3] = create_converter((void *)conv_string, 'p');
	return (converter_list);
}
