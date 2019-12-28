/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:05:00 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/28 18:50:17 by jkauppi          ###   ########.fr       */
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

static unsigned long long	get_decimals(size_t precision, double nbr,
																int neg)
{
	while (precision--)
		nbr *= 10;
	nbr *= 10;
	return (unsign((long long)nbr, neg));
}

static unsigned long long	count_decimals(size_t precision,
						unsigned long long nbr_decimal, char *s, size_t base)
{
	size_t		num_of_zeros;
	size_t		num_of_chars;
	size_t		decrease;

	num_of_chars = ft_numlen(nbr_decimal, base) - 1;
//	nbr_decimal *= 10;
	nbr_decimal += 5;
	nbr_decimal /= 10;
	if (num_of_chars != ft_numlen(nbr_decimal, base))
	{
		decrease = 10;
		while (--num_of_chars)
			decrease *= 10;
		nbr_decimal -= decrease;
	}
	num_of_chars = ft_numlen(nbr_decimal, base);
	num_of_zeros = precision - num_of_chars;
	while (num_of_zeros--)
		s = ft_strcat(s, "0");
	return (nbr_decimal);
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

char						*ft_dtoa_base(double nbr, size_t base,
															size_t precision)
{
	char					*s;
	int						neg;
	size_t					num_of_chars;
	unsigned long long		nbr_integer;
	unsigned long long		nbr_decimal;

	neg = 0;
	if (nbr < 0 && base == 10)
		neg = 1;
	nbr_integer = unsign((long long)nbr, neg);
	num_of_chars = ft_numlen(nbr_integer, base);
	s = (char *)ft_strnew(sizeof(*s) * (num_of_chars + precision + neg + 1));
	if (neg)
		s = ft_strcat(s, "-");
	add_digits(s, nbr_integer, base);
	s = ft_strcat(s, ".");
	nbr -= (long long)nbr;
	nbr_decimal = get_decimals(precision, nbr, neg);
	nbr_decimal = count_decimals(precision, nbr_decimal, s, base);
	add_digits(s, nbr_decimal, base);
	return (s);
}
