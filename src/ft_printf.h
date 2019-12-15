/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:23:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/15 18:56:43 by jkauppi          ###   ########.fr       */
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

enum				e_type
{
	hh,
	h,
	l,
	ll,
	j,
	z,
	t,
	L
};

typedef enum e_type			t_type;

struct				s_formatter
{
	char			character;
	t_flag			flag;
	void			*(*function_ptr)(char *s, char character);
};

typedef struct s_formatter	t_formatter;

struct				s_converter
{
	char			character;
	int				valid_flags;
	void			*(*function_ptr)(va_list *, void *substring, int *attrs);
};

typedef struct s_converter	t_converter;

struct				s_substring
{
	char			*input_string;
	t_converter		*converter;
	int				flags;
	t_list			**formatter_list;
	char			*output_string;
};

typedef struct s_substring	t_substring;

t_list				**split_string(char *input_string,
										t_list **converter_array);
t_list				**create_formatters(void);
t_list				**create_converters(void);
t_list				**create_param_type_list(void);
void				add_param_type(t_list **list, t_list **type_list);
int					convert_substrings(t_list **list, va_list *ap,
												t_list **converter_list,
												t_list **formatter_list);
char				*ft_ltoa_base(long nbr, int base);
t_list				**get_formatters(char *input_string, int valid_flags,
												t_list **formatter_list);
char				*format_string(char *output_string,
												t_substring *substring);

#endif
