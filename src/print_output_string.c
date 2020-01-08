/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/08 21:55:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	size_t	count_len(t_substring *substring)
{
	size_t		string_len;

	string_len = 0;
	string_len += substring->o_string.pre_filler.content_size;
	string_len += substring->o_string.sign.content_size;
	string_len += substring->o_string.prefix.content_size;
	string_len += substring->o_string.zero_filler.content_size;
	string_len += substring->o_string.parameter.content_size;
	string_len += substring->o_string.post_filler.content_size;
	return (string_len);
}

static void		add_substrings(t_substring *substring, char *s)
{
	size_t				i;
	t_output_string		o_s;

	o_s = substring->o_string;
	i = 0;
	if (o_s.pre_filler.content)
		ft_strcat(s + i, o_s.pre_filler.content);
	if (o_s.sign.content)
		ft_strcat((s += o_s.pre_filler.content_size), o_s.sign.content);
	if (o_s.prefix.content)
		ft_strcat((s += o_s.sign.content_size), o_s.prefix.content);
	if (o_s.zero_filler.content)
		ft_strcat((s += o_s.prefix.content_size), o_s.zero_filler.content);
	if (o_s.parameter.content)
	{
		if (o_s.add_null)
			ft_strcat((s += o_s.zero_filler.content_size), "");
		else
			ft_strcat((s += o_s.zero_filler.content_size),
													o_s.parameter.content);
	}
	if (o_s.post_filler.content)
		ft_strcat((s += o_s.parameter.content_size), o_s.post_filler.content);
	return ;
}

static void		write_output_string(size_t *words, t_substring *substring)
{
	size_t		string_len;
	char		*s;

	string_len = count_len(substring);
	*words += string_len;
	if (string_len)
	{
		s = ft_strnew(string_len);
		s[0] = '\0';
		add_substrings(substring, s);
		ft_putlstr(s, string_len);
		ft_strdel(&s);
	}
}

static int		is_null(t_substring *substring, size_t *words)
{
	size_t		c;
	size_t		len;

	if (substring->converter && substring->converter->character == 'c')
	{
		len = ft_strlen(substring->output_string);
		c = -1;
		while (++c < len)
		{
			if (substring->output_string[c] == 0x01 &&
												substring->o_string.add_null)
				ft_putchar('\0');
			else
				ft_putchar(substring->output_string[c]);
		}
		*words += len;
		return (1);
	}
	else
		return (0);
}

size_t			print_formatted_string(t_list **substring_list)
{
	t_list			*substring_elem;
	t_substring		*substring;
	size_t			words;

	words = 0;
	substring_elem = *substring_list;
	while (substring_elem)
	{
		substring = (t_substring *)(substring_elem->content);
		if (substring->converter && (substring->converter->character == 'f' ||
									substring->converter->character == 'o' ||
									substring->converter->character == 'd' ||
									substring->converter->character == 'i' ||
									substring->converter->character == 'u' ||
									substring->converter->character == 'x' ||
									substring->converter->character == 'X' ||
									substring->converter->character == 'p' ||
									substring->converter->character == '%' ||
									substring->converter->character == 's' ||
									substring->converter->character == 'c'))
			write_output_string(&words, substring);
		else if (substring->output_string)
		{
			if (!is_null(substring, &words))
			{
				ft_putstr(substring->output_string);
				words += ft_strlen(substring->output_string);
			}
		}
		substring_elem = substring_elem->next;
	}
	return (words);
}
