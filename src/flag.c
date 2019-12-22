/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:59:09 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/22 14:02:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*format_string(char *s, t_substring *substring)
{
	t_list			*elem;
	t_formatter		*formatter;
	char			*output_string;
	char			*tmp;
	char			character;

	output_string = s;
	elem = *substring->formatter_list;
	while (elem)
	{
		formatter = (t_formatter *)(elem->content);
		tmp = output_string;
		character = substring->converter->character;
		output_string = formatter->function_ptr(substring, tmp, character);
		elem = elem->next;
	}
	return (output_string);
}

static char		*format_minus(t_substring *substring, char *s, char character)
{
	(void)character;
	substring->left_adjust = 1;
	return (s);
}

static char		*format_plus(t_substring *substring, char *s, char character)
{
	char		*new_string;

	(void)substring;
	if (character == 'c')
		new_string = ft_strdup(s);
	else if (character == 's')
		new_string = ft_strdup(s);
	else if (character == 'd' || character == 'i')
		if (s[0] == '-')
			new_string = ft_strdup(s);
		else
			new_string = ft_strjoin("+", s);
	else
		new_string = ft_strdup(s);
	ft_strdel(&s);
	return (new_string);
}

static char		*format_space(t_substring *substring, char *s, char character)
{
	char		*new_string;

	(void)substring;
	if (character == 'c')
		new_string = ft_strdup(s);
	else if (character == 's')
		new_string = ft_strdup(s);
	else if (character == 'd' || character == 'i')
	{
		if (*s == '-')
			new_string = ft_strdup(s);
		else if (*s == '+')
			new_string = ft_strdup(s);
		else
			new_string = ft_strjoin(" ", s);
	}
	else if (character == 'u')
		new_string = ft_strdup(s);
	else
		new_string = ft_strjoin(" ", s);
	ft_strdel(&s);
	return (new_string);
}

static char		*format_zero(t_substring *substring, char *s, char character)
{
	(void)character;
	substring->filler = '0';
	return (s);
}

static char		*format_hash(t_substring *substring, char *s, char character)
{
	char		*new_string;

	(void)substring;
	if (character == 'x')
		new_string = ft_strjoin("0x", s);
	else if (character == 'X')
		new_string = ft_strjoin("0X", s);
	else if (character == 'o')
		new_string = ft_strjoin("0", s);
	else if (character == 'c')
		new_string = ft_strdup(s);
	else
		new_string = ft_strdup(s);
	ft_strdel(&s);
	return (new_string);
}

void			get_formatters(t_substring *substring, t_list **formatter_list)
{
	int				s_len;
	t_list			*elem;
	t_formatter		*formatter;

	elem = *formatter_list;
	while (elem)
	{
		formatter = (t_formatter *)elem->content;
		s_len = substring->end_ptr - substring->input_string + 1;
		while (s_len--)
		{
			if (substring->input_string[s_len] == formatter->character &&
				!(substring->flags & formatter->flag))
			{
				substring->flags |= formatter->flag;
				ft_lstadd_e(substring->formatter_list,
					ft_lstnew(elem->content, elem->content_size));
				break ;
			}
		}
		elem = elem->next;
	}
}

static t_list	*new_formatter(void *function, char character, t_flag flag)
{
	t_formatter		*formatter;
	size_t			formatter_size;
	t_list			*elem;

	formatter_size = sizeof(*formatter);
	formatter = (t_formatter *)ft_memalloc(formatter_size);
	formatter->character = character;
	formatter->flag = flag;
	formatter->function_ptr = function;
	elem = (t_list *)ft_memalloc(sizeof(*elem));
	elem->content = (void *)formatter;
	elem->content_size = formatter_size;
	elem->next = NULL;
	return (elem);
}

t_list			**create_formatters(void)
{
	t_list			**formatter_list;

	formatter_list = (t_list **)ft_memalloc(sizeof(*formatter_list));
	ft_lstadd_e(formatter_list, new_formatter((void *)format_minus, '-',
																	minus));
	ft_lstadd_e(formatter_list, new_formatter((void *)format_plus, '+', plus));
	ft_lstadd_e(formatter_list, new_formatter((void *)format_space, ' ',
																	space));
	ft_lstadd_e(formatter_list, new_formatter((void *)format_zero, '0', zero));
	ft_lstadd_e(formatter_list, new_formatter((void *)format_hash, '#', hash));
	return (formatter_list);
}
