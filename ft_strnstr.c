/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:43:02 by lbuccher          #+#    #+#             */
/*   Updated: 2021/12/21 13:43:25 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!ft_strlen(little) || big == little)
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] && big[i + j] == little[j] && i + j < len)
				j++;
			if (!little[j])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
