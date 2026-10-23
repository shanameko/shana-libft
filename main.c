#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "libft.h"

static int	g_fail = 0;

static void	check(const char *name, int ok)
{
	printf("%-28s %s\n", name, ok ? "OK" : "KO");
	if (!ok)
		g_fail++;
}

static void	test_calloc(void)
{
	int		*arr;
	char	*zero;
	void	*big;
	int		ok;
	int		i;

	arr = ft_calloc(5, sizeof(int));
	ok = (arr != NULL);
	i = 0;
	while (ok && i < 5)
	{
		if (arr[i] != 0)
			ok = 0;
		i++;
	}
	check("calloc: 5 ints are zero", ok);
	free(arr);

	zero = ft_calloc(0, 4);
	check("calloc: nmemb 0 not NULL", zero != NULL);
	free(zero);

	zero = ft_calloc(4, 0);
	check("calloc: size 0 not NULL", zero != NULL);
	free(zero);

	big = ft_calloc(SIZE_MAX, 2);
	check("calloc: overflow gives NULL", big == NULL);
}

static void	test_strdup(void)
{
	char	src[] = "hello";
	char	*d;
	char	*e;

	d = ft_strdup(src);
	check("strdup: same content", d && strcmp(d, src) == 0);
	check("strdup: different pointer", d != src);
	if (d)
	{
		d[0] = 'J';
		check("strdup: original untouched", strcmp(src, "hello") == 0);
		check("strdup: copy changed", strcmp(d, "Jello") == 0);
	}
	free(d);

	e = ft_strdup("");
	check("strdup: empty string", e && e[0] == '\0');
	free(e);

	e = ft_strdup("a longer string with spaces");
	check("strdup: longer string",
		e && strcmp(e, "a longer string with spaces") == 0);
	free(e);
}

int	main(void)
{
	test_calloc();
	test_strdup();
	if (g_fail == 0)
		printf("\nAll tests passed.\n");
	else
		printf("\n%d test(s) failed.\n", g_fail);
	return (g_fail != 0);
}