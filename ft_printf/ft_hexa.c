/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:03:48 by nadesjar          #+#    #+#             */
/*   Updated: 2022/04/28 12:24:33 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_len(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

int	ft_puthexa(unsigned int nbr, char c)
{
	int	len;

	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr >= 16)
	{
		ft_puthexa(nbr / 16, c);
		ft_puthexa(nbr % 16, c);
	}
	else
	{
		if (c == 'x')
			ft_putchar_fd("0123456789abcdef"[nbr % 16], 1);
		else if (c == 'X')
			ft_putchar_fd("0123456789ABCDEF"[nbr % 16], 1);
	}
	len = ft_hexa_len(nbr);
	return (len);
}

int	ft_put_unsigned(unsigned int nbr)
{
	int	len;

	len = ft_nbrlen(nbr);
	if (nbr > 9)
		ft_put_unsigned(nbr / 10);
	ft_putchar_fd("0123456789"[nbr % 10], 1);
	return (len);
}

int	ft_ptr_len(unsigned long int nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

int	ft_putptr(unsigned long int nbr, int i)
{
	if (i == 1)
	{
		ft_putstr("0x");
		if (nbr == 0)
		{
			ft_putchar_fd('0', 1);
			return (3);
		}
	}
	if (nbr >= 16)
	{
		ft_putptr(nbr / 16, 0);
		ft_putptr(nbr % 16, 0);
	}
	else
		ft_putchar_fd("0123456789abcdef"[nbr % 16], 1);
	return (ft_ptr_len(nbr) + 2);
}
