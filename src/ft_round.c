/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 08:12:32 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 19:57:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double			ft_round(double nbr, int base, size_t precision, int neg)
{
	double		round_value;
	size_t		c;

	(void)neg;
	round_value = (double)(base / 2);
	c = 0;
	while (c++ < precision)
		nbr *= base;
	nbr *= base;
	if ((int)nbr % 10 >= 5)
		nbr = nbr / base + 1;
	else if ((int)nbr % 10 <= -5)
		nbr = nbr / base - 1;
	else
		nbr /= base;
	c = 0;
	while (c++ < precision)
		nbr /= base;
	return (nbr);
}

	// double		round_value;

	// round_value = (double)(base / 2);
	// while (precision--)
	// 	round_value /= base;
	// round_value /= base;
	// if (neg)
	// 	nbr -= round_value;
	// else
	// 	nbr += round_value;
	// return (nbr);
