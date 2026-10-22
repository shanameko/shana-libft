#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*p2;
	size_t	i;

	p = (unsigned char *)src;
	p2 = (unsigned char *)dest;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			p2[i] = p[i];
			i++;
		}
	}
	else if (dest > src)
	{
		while (n > 0)
		{
			n--;
			p2[n] = p[n];
		}
	}
	return (dest);
}