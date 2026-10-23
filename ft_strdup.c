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