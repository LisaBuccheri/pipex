/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:57:14 by lbuccher          #+#    #+#             */
/*   Updated: 2021/12/21 13:57:37 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;

	len = ft_strlen(s);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	len = -1;
	while (s[++len])
		dest[len] = s[len];
	dest[len] = 0;
	return (dest);
}
