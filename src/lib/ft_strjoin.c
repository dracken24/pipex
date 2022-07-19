/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:42:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/12 20:09:23 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static char	*ft_joint(char *restrict dest, const char *restrict str)
{
	int	i;
	int	k;

	i = 0;
	while (dest[i] != '\0')
		i++;
	k = 0;
	while (str[k] != '\0')
		dest[i++] = str[k++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	str = ft_joint(str, (char *) s1);
	str = ft_joint(str, (char *) s2);
	return (str);
}
