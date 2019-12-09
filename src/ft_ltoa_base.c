/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:59:01 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/09 12:48:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				count_chars(unsigned long nbr, int base)
{
	int		c;

	c = 1;
	while (nbr /= base)
		c++;
	return (c);
}

static unsigned long	unsign(long nbr, int neg)
{
	if (neg)
		return (unsigned long)(nbr * -1);
	else
		return (unsigned long)(nbr);
}

static char				*long_to_string(long nbr, int base, int index, char *s)
{
	static char		*letter = "0123456789abcdef";

	if (nbr >= base)
		long_to_string(nbr / base, base, index - 1, s);
	s[index] = letter[nbr % base];
	return (s);
}

char					*ft_ltoa_base(long nbr, int base)
{
	char			*s;
	int				neg;
	int				num_of_chars;
	unsigned long	un_nbr;

	neg = 0;
	if (nbr < 0 && base == 10)
		neg = 1;
	un_nbr = unsign(nbr, neg);
	num_of_chars = count_chars(un_nbr, base);
	s = (char *)ft_strnew(sizeof(*s) * (num_of_chars + neg));
	if (neg)
		s[0] = '-';
	s = long_to_string(un_nbr, base, num_of_chars + neg - 1, s);
	return (ft_strjoin("0x", s));
}
