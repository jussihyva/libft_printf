/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:59:09 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/12 18:51:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*format_string(char *s, t_list **formatter_list)
{
	t_list			*elem;
	t_formatter		*formatter;
	char			*output_string;
	char			*tmp;

	output_string = s;
	elem = *formatter_list;
	while (elem)
	{
		formatter = (t_formatter *)(elem->content);
		tmp = output_string;
		output_string = formatter->function_ptr(tmp);
		elem = elem->next;
	}
	return (output_string);
}

static char		*format_minus(char *s)
{
	return (s);
}

static char		*format_plus(char *s)
{
	char		*new_string;

	if (s[0] != '-')
		new_string = ft_strjoin("+", s);
	else
		new_string = ft_strdup(s);
	ft_strdel(&s);
	return (new_string);
}

static char		*format_space(char *s)
{
	return (s);
}

static char		*format_zero(char *s)
{
	return (s);
}

static char		*format_hash(char *s)
{
	char		*new_string;

	if (s[0] != '#')
		new_string = ft_strjoin("0x", s);
	else
		new_string = ft_strdup(s);
	ft_strdel(&s);
	return (new_string);
}

int				parse_flags(char *s, int valid_flags, t_list **formatter_list)
{
	int		i;
	int		s_len;
	int		flags;
	t_list	*elem;

	(void)valid_flags;
	s_len = ft_strlen(s);
	if (s[0] != '%' || s[s_len - 1] == '%')
		flags = 0;
	else
	{
		flags = 0;
		i = 0;
		while (++i < (s_len - 1))
		{
			elem = *formatter_list;
			while (elem)
			{
				if (s[i] == ((t_formatter *)(elem->content))->character)
					flags |= ((t_formatter *)(elem->content))->flag;
				elem = elem->next;
			}
		}
	}
	return (flags);
}

t_list				**get_formatters(char *s, int valid_flags,
												t_list **formatter_list)
{
	int		i;
	int		s_len;
	int		flags;
	t_list	**valid_formatters_list;
	t_list	*elem;
	t_list	*new_elem;

	valid_formatters_list = (t_list **)ft_memalloc(sizeof(*valid_formatters_list));
	(void)valid_flags;
	s_len = ft_strlen(s);
	if (s[0] != '%' || s[s_len - 1] == '%')
		flags = 0;
	else
	{
		flags = 0;
		i = 0;
		while (++i < (s_len - 1))
		{
			elem = *formatter_list;
			while (elem)
			{
				if (s[i] == ((t_formatter *)(elem->content))->character)
				{
					flags |= ((t_formatter *)(elem->content))->flag;
					new_elem = ft_lstnew(elem->content, elem->content_size);
					ft_lstadd_e(valid_formatters_list, new_elem);
				}
				elem = elem->next;
			}
		}
	}
	return (valid_formatters_list);
}

static t_list	*new_formatter(void *function, char character, t_flag flag)
{
	t_formatter		*formatter;
	t_list			*elem;

	formatter = (t_formatter *)ft_memalloc(sizeof(*formatter));
	formatter->character = character;
	formatter->flag = flag;
	formatter->function_ptr = function;
	elem = (t_list *)ft_memalloc(sizeof(*elem));
	elem->content = (void *)formatter;
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
