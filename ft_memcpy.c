/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenboua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 15:46:37 by obenboua          #+#    #+#             */
/*   Updated: 2026/10/23 15:46:38 by obenboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *p;
	unsigned char *p2;
	size_t i;

	p = (unsigned char *)src;
	p2 = (unsigned char *)dest;
	i = 0;

	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		p2[i] = p[i];
		i++;
	}
	return (dest);
}
