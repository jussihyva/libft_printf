/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/15 18:42:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			add_converter(t_substring *substring,
										t_list **converter_list,
										t_list **formatter_list)
{
	char			character;
	char			*input_string;
	t_list			*elem;

	input_string = substring->input_string;
	character = input_string[ft_strlen(input_string) - 1];
	elem = *converter_list;
	while (elem)
	{
		if (character == ((t_converter *)(elem->content))->character)
		{
			substring->converter = (t_converter *)(elem->content);
			if (input_string[0] == '%' &&
							input_string[ft_strlen(input_string) - 1] != '%')
				substring->formatter_list = get_formatters(input_string,
										substring->converter->valid_flags,
										formatter_list);
			break ;
		}
		elem = elem->next;
	}
}

static void			convert_substring(t_substring *substring, va_list *ap,
											int *attrs)
{
	if (!substring->converter || !substring->converter->function_ptr)
		substring->output_string = ft_strdup(substring->input_string);
	else
	{
		substring->output_string = substring->converter->function_ptr(ap,
									substring, attrs);
	}
	return ;
}

int					convert_substrings(t_list **list, va_list *ap,
											t_list **converter_list,
											t_list **formatter_list)
{
	t_list			*elem;
	t_substring		*substring;
	int				attrs;
	int				max_num_attrs;

	max_num_attrs = 190;
	attrs = 0;
	elem = *list;
	while (elem)
	{
		substring = (t_substring *)(elem->content);
		substring->converter = NULL;
		substring->flags = 0;
		add_converter(substring, converter_list, formatter_list);
		convert_substring(substring, ap, &attrs);
		elem = elem->next;
	}
	return (attrs);
}

static char			*no_conv(va_list *ap, t_substring *substring,
															int *attrs)
{
	char			*input_string;

	input_string = substring->input_string;
	(void)ap;
	(void)*attrs;
	input_string[ft_strlen(input_string) - 1] = '\0';
	return (ft_strdup(input_string));
}

static char			*conv_character(va_list *ap, t_substring *substring,
															int *attrs)
{
	char		*s;
	char		*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	s = ft_strnew(1);
	s[0] = (char)va_arg(*ap, int);
	return (s);
}

static char			*conv_string(va_list *ap, t_substring *substring,
															int *attrs)
{
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	return (ft_strdup(va_arg(*ap, char *)));
}

static char			*conv_pointer(va_list *ap, t_substring *substring,
															int *attrs)
{
	uintptr_t		ptr;
	char			*ptr_string;
	char			*s;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	ptr = (uintptr_t)(va_arg(*ap, void *));
	ptr_string = ft_ltoa_base(ptr, 16);
	s = ft_strjoin("0x", ptr_string);
	ft_strdel(&ptr_string);
	return (s);
}

static char			*conv_int(va_list *ap, t_substring *substring,
															int *attrs)
{
	int				nbr;
	char			*s;
	char			*output_string;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	nbr = (int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 10);
	output_string = format_string(s, substring);
	return (output_string);
}

static char			*conv_unsigned_octal(va_list *ap, t_substring *substring,
															int *attrs)
{
	unsigned int	nbr;
	char			*s;
	char			*output_string;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 8);
	output_string = format_string(s, substring);
	return (output_string);
}

static char			*conv_unsigned_int(va_list *ap, t_substring *substring,
															int *attrs)
{
	unsigned int	nbr;
	char			*s;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 10);
	return (s);
}

static char			*conv_unsigned_hex(va_list *ap, t_substring *substring,
															int *attrs)
{
	unsigned int	nbr;
	char			*s;
	char			*output_string;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 16);
	output_string = format_string(s, substring);
	return (output_string);
}

static char			*conv_unsigned_hex_up(va_list *ap, t_substring *substring,
															int *attrs)
{
	unsigned int	nbr;
	char			*s;
	char			*output_string;
	int				i;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 16);
	output_string = format_string(s, substring);
	i = -1;
	while (*(output_string + ++i))
		*(output_string + i) = ft_toupper(*(output_string + i));
	return (output_string);
}

static char			*conv_float(va_list *ap, t_substring *substring,
															int *attrs)
{
	unsigned long	tmp;
	double			nbr;
	char			*s;
	char			*input_string;

	input_string = substring->input_string;
	(void)input_string;
	(*attrs)++;
	nbr = (double)(va_arg(*ap, double));
	tmp = (unsigned long)nbr;
	nbr *= 1000000;
	s = ft_ltoa_base(nbr, 10);
	return (s);
}

static t_list		*new_conv(void *function, char character,
									int valid_flags)
{
	t_converter		*converter;
	size_t			converter_size;
	t_list			*elem;

	converter_size = sizeof(*converter);
	converter = (t_converter *)ft_memalloc(converter_size);
	converter->character = character;
	converter->valid_flags = valid_flags;
	converter->function_ptr = function;
	elem = (t_list *)ft_memalloc(sizeof(*elem));
	elem->content = (void *)converter;
	elem->content_size = converter_size;
	elem->next = NULL;
	return (elem);
}

t_list				**create_converters(void)
{
	t_list			**conv_list;
	int				valid_flags;

	conv_list = (t_list **)ft_memalloc(sizeof(*conv_list));
	valid_flags = 0;
	ft_lstadd_e(conv_list, new_conv((void *)no_conv, '%', valid_flags));
	valid_flags = 0;
	valid_flags |= plus;
	ft_lstadd_e(conv_list, new_conv((void *)conv_character, 'c', valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_string, 's', valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_pointer, 'p', valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_int, 'd', valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_int, 'i', valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_octal, 'o',
															valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_int, 'u',
															valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_hex, 'x',
															valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_hex_up, 'X',
															valid_flags));
	ft_lstadd_e(conv_list, new_conv((void *)conv_float, 'f', valid_flags));
	return (conv_list);
}
