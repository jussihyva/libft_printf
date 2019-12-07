/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:23:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/07 17:10:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>

# define NUM_OF_CONVERTERS 4

struct						s_converter
{
	char		character;
	void		*(*function_ptr)(va_list *);
};

typedef struct s_converter		t_converter;

struct						s_substring
{
	char			*input_string;
	t_converter		*converter;
	char			*output_string;
};

typedef struct s_substring		t_substring;

t_list			**split_input_string(char *input_string,
							t_converter **converter_array);
t_converter		**create_converters();
void			add_converter(t_substring *substring,
							t_converter **converter_list);
void			convert_substring(t_substring *substring, va_list *ap);

#endif
