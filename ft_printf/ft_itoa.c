/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:46:36 by marvin            #+#    #+#             */
/*   Updated: 2022/06/19 16:19:51 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bzero(void *str, size_t len)
{
	ft_memset(str, '\0', len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(size * count);
	if (!str)
		return (NULL);
	ft_bzero(str, size * count);
	return (str);
}

static char	*ft_transfert(char *x, unsigned int number, long int len)
{
	while (number > 0)
	{
		x[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (x);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		len;
	unsigned int	numb;

	len = ft_len(n);
	str = ft_calloc((len + 1), sizeof(char));
	if (!(str))
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		numb = n * -1;
		str[0] = '-';
	}
	else
		numb = n;
	str = ft_transfert(str, numb, len);
	return (str);
}
