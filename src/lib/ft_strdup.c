/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:34:41 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/12 20:08:57 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*ft_strdup(char *src)
{
	char	*cpstr;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	cpstr = ft_calloc(sizeof(char), (len + 1));
	if (!cpstr)
		return (NULL);
	while (src[i] != '\0')
	{
		cpstr[i] = src[i];
		i++;
	}
	cpstr[i] = '\0';
	return (cpstr);
}
