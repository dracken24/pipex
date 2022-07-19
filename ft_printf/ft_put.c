/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:43:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/04/26 14:56:27 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putstr(const char *str)
{
	size_t	len;

	len = -1;
	if (!str)
	{
		len = ft_putstr("(null)");
		return (len);
	}
	while (str[++len] != '\0')
		write(1, &str[len], 1);
	return (len);
}

int	ft_put_nbr(int n)
{
	char	*numb;
	int		len;

	len = 0;
	numb = ft_itoa(n);
	len = ft_putstr(numb);
	free (numb);
	return (len);
}

int	ft_putpcent(void)
{
	write(1, "%", 1);
	return (1);
}

size_t	ft_nbrlen(long long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
