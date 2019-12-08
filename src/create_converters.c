/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/08 09:05:29 by jkauppi          ###   ########.fr       */
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

void				convert_substring(t_substring *substring, va_list *ap)
{
	(void)ap;
	if (!substring->converter || !substring->converter->function_ptr)
		substring->output_string = substring->input_string;
	else
		substring->output_string = substring->converter->function_ptr(ap, substring->input_string);
	return ;
}

static char			*no_conv(va_list *ap, char *input_string)
{
	(void)ap;
	input_string[ft_strlen(input_string) - 1] = '\0';
	return (input_string);
}

static char			*conv_character(va_list *ap, char *input_string)
{
	char		*s;

	(void)input_string;
	s = ft_strnew(1);
	s[0] = (char)va_arg(*ap, int);
	return (s);
}

static char			*conv_string(va_list *ap, char *input_string)
{
	(void)input_string;
	return (va_arg(*ap, char *));
}

static char			*conv_pointer(va_list *ap, char *input_string)
{
	(void)input_string;
	return (ft_itoa(va_arg(*ap, long long)));
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
	converter_list[3] = create_converter((void *)conv_pointer, 'p');
	return (converter_list);
}
