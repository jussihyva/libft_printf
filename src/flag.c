/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:59:09 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 18:12:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*format_minus(t_substring *substring, char *s, char character)
{
	char		*new_string;

	(void)character;
	substring->left_adjust = 1;
	new_string = ft_strdup(s);
	ft_strdel(&s);
	return (new_string);
}

char		*format_plus(t_substring *substring, char *s, char character)
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

char		*format_space(t_substring *substring, char *s, char character)
{
	char		*new_string;

	(void)substring;
	if (character == 'c')
		new_string = ft_strdup(s);
	else if (character == 's')
		new_string = ft_strdup(s);
	else if (character == '%')
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

char		*format_zero(t_substring *substring, char *s, char character)
{
	char		*new_string;

	(void)character;
	substring->filler = '0';
	new_string = ft_strdup(s);
	ft_strdel(&s);
	return (new_string);
}

char		*format_hash(t_substring *substring, char *s, char character)
{
	char		*new_string;

	(void)substring;
	if (character == 'x' || character == 'X')
	{
		if (s[0] == '0')
			new_string = ft_strdup(s);
		else
			new_string = ft_strjoin("0x", s);
	}
	else if (character == 'o')
		new_string = ft_strjoin("0", s);
	else if (character == 'c')
		new_string = ft_strdup(s);
	else
		new_string = ft_strdup(s);
	ft_strdel(&s);
	return (new_string);
}
