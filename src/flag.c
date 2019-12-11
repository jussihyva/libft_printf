/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:59:09 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/11 16:26:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		get_flag(char c)
{
	if (c == '-')
		return (minus);
	else if (c == '+')
		return (plus);
	else if (c == ' ')
		return (space);
	else if (c == '0')
		return (zero);
	else if (c == '#')
		return (hash);
	else
		return (0);
}

/*
static char		*format_plus(char *s)
{
	return (s);
}
*/

int				parse_flags(char *s, int valid_flags)
{
	int		i;
	int		s_len;
	int		flags;
	char	*ptr;

	(void)valid_flags;
	s_len = ft_strlen(s);
	i = 1;
	if (s[0] != '%' || s[s_len - 1] == '%')
		flags = 0;
	else
	{
		flags = 0;
		i = 0;
		while (++i < (s_len - 1))
		{
			if ((ptr = ft_strchr("-+ 0#", s[i])))
				flags |= get_flag(*ptr);
		}
	}
	return (flags);
}

t_list			**create_formatters(void)
{
	t_list			**formatter_list;

	formatter_list = (t_list **)ft_memalloc(sizeof(*formatter_list));
	return (formatter_list);
}
