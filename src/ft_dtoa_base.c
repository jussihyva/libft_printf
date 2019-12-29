/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:05:00 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 18:18:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	unsign(long long nbr, int neg)
{
	if (neg)
		return (unsigned long long)(nbr * -1);
	else
		return (unsigned long long)(nbr);
}

static char					*long_to_string(unsigned long long nbr,
									unsigned int base, size_t index, char *s)
{
	static char		*letter = "0123456789abcdef";

	while (nbr >= (unsigned long long)base)
	{
		s[--index] = letter[nbr % base];
		nbr /= base;
	}
	s[--index] = letter[nbr % base];
	return (s);
}

static size_t				get_decimals(size_t precision, long double *nbr,
																	char *s)
{
	static size_t	max_precision = 20;
	size_t			added_zeros;
	size_t			c;

	added_zeros = 0;
	c = 0;
	while (c++ < precision && c < max_precision)
	{
		*nbr *= 10;
		if (*nbr < 1 && *nbr > -1)
		{
			s = ft_strcat(s, "0");
			added_zeros++;
		}
	}
	return (added_zeros);
}

static void					add_digits(char *s, unsigned long long un_nbr,
													size_t base)
{
	char					*sub_string;
	size_t					num_of_chars;

	num_of_chars = ft_numlen(un_nbr, base);
	sub_string = ft_strnew(num_of_chars);
	s = ft_strcat(s, long_to_string(un_nbr, base, num_of_chars, sub_string));
	ft_strdel(&sub_string);
	return ;
}

char						*ft_dtoa_base(long double nbr, size_t base,
												size_t precision, int add_dot)
{
	char					*s;
	int						neg;
	unsigned long long		nbr_integer;
	unsigned long long		nbr_decimal;
	size_t					added_zeros;

	neg = 0;
	if (nbr < 0 && base == 10)
		neg = 1;
	nbr = ft_round(nbr, base, precision, neg);
	nbr_integer = unsign((long long)nbr, neg);
	s = (char *)ft_strnew((ft_numlen(nbr_integer, base) + precision + neg + 1));
	if (neg)
		s = ft_strcat(s, "-");
	add_digits(s, nbr_integer, base);
	nbr -= (long long)nbr;
	if (precision || add_dot)
		s = ft_strcat(s, ".");
	added_zeros = get_decimals(precision, &nbr, s);
	nbr_decimal = unsign((long long)nbr, neg);
	if (nbr_decimal)
		add_digits(s, nbr_decimal, base);
	while (added_zeros++ + ft_numlen(nbr_decimal, base) < precision)
		s = ft_strcat(s, "0");
	return (s);
}
