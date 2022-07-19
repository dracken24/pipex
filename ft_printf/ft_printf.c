/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:29:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/04/27 12:07:48 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_choose_action(va_list choose, const char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(choose, int));
	else if (c == 's')
		len += ft_putstr(va_arg(choose, char *));
	else if (c == 'd' || c == 'i')
		len += ft_put_nbr(va_arg(choose, int));
	else if (c == '%')
		len += ft_putpcent();
	else if (c == 'x' || c == 'X')
		len += ft_puthexa(va_arg(choose, unsigned int), c);
	else if (c == 'u')
		len += ft_put_unsigned(va_arg(choose, unsigned int));
	else if (c == 'p')
		len += ft_putptr(va_arg(choose, unsigned long int), 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	choose;
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	va_start(choose, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_choose_action(choose, str[i + 1]);
			i++;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(choose);
	return (len);
}

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *) str)[i] = (char) c;
		i++;
	}
	return (str);
}
