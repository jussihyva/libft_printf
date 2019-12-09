/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/09 18:22:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				add_converter(t_substring *substring,
							t_list **converter_list)
{
	char			character;
	char			*input_string;
	int				i;
	t_list			*elem;

	input_string = substring->input_string;
	character = input_string[ft_strlen(input_string) - 1];
	i = -1;
	substring->converter = NULL;
	elem = *converter_list;
	while (elem)
	{
		if (character == ((t_converter *)(elem->content))->character)
			substring->converter = (t_converter *)(elem->content);
		elem = elem->next;
	}
}

static void			convert_substring(t_substring *substring, va_list *ap,
											int *attrs)
{
	if (!substring->converter || !substring->converter->function_ptr)
		substring->output_string = ft_strdup(substring->input_string);
	else
		substring->output_string = substring->converter->function_ptr(ap,
									substring->input_string, attrs);
	return ;
}

int					convert_substrings(t_list **list, va_list *ap,
											t_list **converter_list)
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
		add_converter(substring, converter_list);
		convert_substring(substring, ap, &attrs);
/*
		ft_putstr(substring->input_string);
		ft_putstr("  ");
		if (substring->converter)
			ft_putchar((substring->converter)->character);
		else
			ft_putstr("null");
		ft_putchar('\n');
*/
		elem = elem->next;
	}
	return (attrs);
}

static char			*no_conv(va_list *ap, char *input_string, int *attrs)
{
	(void)ap;
	(void)*attrs;
	input_string[ft_strlen(input_string) - 1] = '\0';
	return (ft_strdup(input_string));
}

static char			*conv_character(va_list *ap, char *input_string, int *attrs)
{
	char		*s;

	(void)input_string;
	(*attrs)++;
	s = ft_strnew(1);
	s[0] = (char)va_arg(*ap, int);
	return (s);
}

static char			*conv_string(va_list *ap, char *input_string, int *attrs)
{
	(void)input_string;
	(*attrs)++;
	return (ft_strdup(va_arg(*ap, char *)));
}

static char			*conv_pointer(va_list *ap, char *input_string, int *attrs)
{
	uintptr_t		ptr;
	char			*ptr_string;
	char			*s;

	(void)input_string;
	(*attrs)++;
	ptr = (uintptr_t)(va_arg(*ap, void *));
	ptr_string = ft_ltoa_base(ptr, 16);
	s = ft_strjoin("0x", ptr_string);
	ft_strdel(&ptr_string);
	return (s);
}

static char			*conv_int(va_list *ap, char *input_string, int *attrs)
{
	int				nbr;
	char			*s;

	(void)input_string;
	(*attrs)++;
	nbr = (int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 10);
	return (s);
}

static char			*conv_unsigned_octal(va_list *ap, char *input_string,
											int *attrs)
{
	unsigned int	nbr;
	char			*s;

	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 8);
	return (s);
}

static char			*conv_unsigned_int(va_list *ap, char *input_string,
											int *attrs)
{
	unsigned int	nbr;
	char			*s;

	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 10);
	return (s);
}

static char			*conv_unsigned_hex(va_list *ap, char *input_string,
											int *attrs)
{
	unsigned int	nbr;
	char			*s;

	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 16);
	return (s);
}

static char			*conv_unsigned_hex_up(va_list *ap, char *input_string,
											int *attrs)
{
	unsigned int	nbr;
	char			*s;
	int				i;

	(void)input_string;
	(*attrs)++;
	nbr = (unsigned int)(va_arg(*ap, void *));
	s = ft_ltoa_base(nbr, 16);
	i = -1;
	while (*(s + ++i))
		*(s + i) = ft_toupper(*(s + i));
	return (s);
}

static char			*conv_float(va_list *ap, char *input_string,
											int *attrs)
{
	unsigned long	tmp;
	double			nbr;
	char			*s;

	(void)input_string;
	(*attrs)++;
//	tmp = (unsigned long)(va_arg(*ap, void *));
	nbr = (double)(va_arg(*ap, double));
	tmp = (unsigned long)nbr;
	nbr *= 1000000;
//	nbr = nbr - (int)(nbr * 1000000);
	s = ft_ltoa_base(nbr, 10);
	return (s);
}

static t_list		*new_conv(void *function, char character)
{
	t_converter		*converter;
	t_list			*elem;

	converter = (t_converter *)ft_memalloc(sizeof(*converter));
	converter->character = character;
	converter->function_ptr = function;
	elem = (t_list *)ft_memalloc(sizeof(*elem));
	elem->content = (void *)converter;
	elem->next = NULL;
	return (elem);
}

t_list				**create_converters(void)
{
	t_list			**converter_list;

	converter_list = (t_list **)ft_memalloc(sizeof(*converter_list));
	ft_lstadd_e(converter_list, new_conv((void *)no_conv, '%'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_character, 'c'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_string, 's'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_pointer, 'p'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_int, 'd'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_int, 'i'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_unsigned_octal, 'o'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_unsigned_int, 'u'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_unsigned_hex, 'x'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_unsigned_hex_up, 'X'));
	ft_lstadd_e(converter_list, new_conv((void *)conv_float, 'f'));
	return (converter_list);
}
