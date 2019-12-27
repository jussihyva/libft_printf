/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:23:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/27 09:16:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>

enum		e_flag
{
	minus = 0x01,
	plus = 0x02,
	space = 0x04,
	zero = 0x08,
	hash = 0x10
};

typedef enum e_flag			t_flag;

enum		e_type
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

struct		s_formatter
{
	char			character;
	t_flag			flag;
	void			*(*function_ptr)(void *substring, char *s, char character);
};

typedef struct s_formatter	t_formatter;

struct		s_converter
{
	char			character;
	int				valid_flags;
	void			*(*function_ptr)(va_list *, void *substring, int *attrs);
	void			*(*adjust_width_prediction_ptr)(void *substring);
};

typedef struct s_converter	t_converter;

struct		s_param_type
{
	t_type			type;
	char			*type_string;
};

typedef struct s_param_type	t_param_type;

struct		s_substring
{
	char			*input_string;
	t_converter		*converter;
	int				flags;
	t_list			**formatter_list;
	char			*output_string;
	t_param_type	*param_type;
	char			*end_ptr;
	int				precision;
	int				width;
	char			filler;
	int				left_adjust;
};

typedef struct s_substring	t_substring;

t_list		**split_string(char *input_string, t_list **converter_array);
t_list		**create_formatters(void);
t_list		**create_converters(void);
t_list		**create_param_type_list(void);
void		add_param_type(t_list **list, t_list **type_list);
void		add_width_and_prediction(t_list **substring_list);
int			convert_substrings(t_list **list, va_list *ap,
							t_list **converter_list, t_list **formatter_list);
void		width_adjust(t_substring *substring);
char		*ft_lltoa_base(long long nbr, int base);
char		*ft_ulltoa_base(unsigned long long nbr, int base);
void		get_formatters(t_substring *substring, t_list **formatter_list);
char		*format_string(char *output_string, t_substring *substring);
char		*modify_substring(t_substring *substring);
void		adjust_character(t_substring *substring);
char		*conv_character(va_list *ap, t_substring *substring, int *attrs);
void		adjust_string(t_substring *substring);
char		*conv_string(va_list *ap, t_substring *substring, int *attrs);
void		adjust_pointer(t_substring *substring);
char		*conv_pointer(va_list *ap, t_substring *substring, int *attrs);
void		adjust_int(t_substring *substring);
char		*conv_int(va_list *ap, t_substring *substring, int *attrs);
void		adjust_unsigned_octal(t_substring *substring);
char		*conv_unsigned_octal(va_list *ap, t_substring *substring,
																int *attrs);
char		*left_adjust(char *string, size_t width);
char		*right_adjust(char filler, char *string, size_t width,
														char *pre_string);
void		adjust_unsigned_int(t_substring *substring);
char		*conv_unsigned_int(va_list *ap, t_substring *substring, int *attrs);
void		add_min_mum_of_digits(t_substring *substring, char *pre_string);
void		add_min_mum_of_chars(t_substring *substring, char *pre_string);
void		adjust_unsigned_hex(t_substring *substring);
char		*conv_unsigned_hex(va_list *ap, t_substring *substring, int *attrs);
char		*conv_unsigned_hex_up(va_list *ap, t_substring *substring,
																int *attrs);
char		*conv_percent_char(va_list *ap, t_substring *substring, int *attrs);
void		adjust_percent_char(t_substring *substring);
long long	read_o_u_x_param(t_type type, va_list *ap);

#endif
