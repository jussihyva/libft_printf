/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:23:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/12 15:03:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>

enum				e_flag
{
	minus = 0x01,
	plus = 0x02,
	space = 0x04,
	zero = 0x08,
	hash = 0x10
};

typedef enum e_flag			t_flag;

struct				s_formatter
{
	char			character;
	t_flag			flag;
	void			*(*function_ptr)(char *s);
};

typedef struct s_formatter	t_formatter;

struct				s_converter
{
	char			character;
	int				valid_flags;
	void			*(*function_ptr)(va_list *, char *input_string, int flags,
										t_list **formatter_list, int *attrs);
};

typedef struct s_converter	t_converter;

struct				s_substring
{
	char			*input_string;
	t_converter		*converter;
	int				flags;
	char			*output_string;
};

typedef struct s_substring	t_substring;

t_list				**split_string(char *input_string,
										t_list **converter_array);
t_list				**create_formatters();
t_list				**create_converters();
int					convert_substrings(t_list **list, va_list *ap,
												t_list **converter_list,
												t_list **formatter_list);
char				*ft_ltoa_base(long nbr, int base);
int					parse_flags(char *input_string, int valid_flags,
												t_list **formatter_list);
char				*format_string(char *output_string, int flags,
										t_list **formatter_list);

#endif
