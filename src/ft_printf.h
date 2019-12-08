/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:23:34 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/08 11:49:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>

struct				s_converter
{
	char			character;
	void			*(*function_ptr)(va_list *, char *input_string);
};

typedef struct s_converter	t_converter;

struct				s_substring
{
	char			*input_string;
	t_converter		*converter;
	char			*output_string;
};

typedef struct s_substring	t_substring;

t_list				**split_string(char *input_string,
										t_list **converter_array);
t_list				**create_converters();
void				add_converter(t_substring *substring,
										t_list **converter_list);
void				convert_substring(t_substring *substring, va_list *ap);

#endif
