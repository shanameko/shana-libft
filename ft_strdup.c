/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenboua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 15:47:31 by obenboua          #+#    #+#             */
/*   Updated: 2026/10/23 15:47:32 by obenboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	k;
	char	*p;

	i = 0;
	while (s[i])
		i++;
	p = malloc(i + 1);
	if(!p)
		return (NULL);
	k = 0;
	while (k <= i)
	{
		p[k] = s[k];
		k++;
	}
	return (p);
}
