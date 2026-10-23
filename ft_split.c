#include "libft.h"

char	**ft_split(char const *s, char c)
{
	size_t i;
	size_t len;
	size_t j;
	size_t k;
	size_t count;
	char **arr;

	count = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (s[0] && s[0] != c)
		count++;
	while(s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c )
		{
			count++;
		}
		i++;
	}
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		while (s[i] && s[i] == c)
			i++;
		len = 0;
		while (s[i + len] && s[i + len] != c)
			len++;
		arr[j] = malloc(len + 1);
		if (!arr)
			return (NULL);
		k = 0;
		while (k < len)
		{
			arr[j][k] = s[i + k];
			k++;
		}
		arr[j][len] = '\0';
		i += len;
		j++;
	}
	arr[j] = NULL;
	return (arr);
}