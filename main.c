#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "libft.h"

static int	g_fail = 0;

static void	check(const char *name, int ok)
{
	printf("%-12s %s\n", name, ok ? "OK" : "KO");
	if (!ok)
		g_fail++;
}

static int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

static void	to_upper_cb(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

static void	index_cb(unsigned int i, char *c)
{
	*c = '0' + (i % 10);
}

static void	test_ctype(void)
{
	int	c;
	int	ok[7];

	for (int k = 0; k < 7; k++)
		ok[k] = 1;
	for (c = 0; c < 256; c++)
	{
		if (!!ft_isalpha(c) != !!isalpha(c))
			ok[0] = 0;
		if (!!ft_isdigit(c) != !!isdigit(c))
			ok[1] = 0;
		if (!!ft_isalnum(c) != !!isalnum(c))
			ok[2] = 0;
		if (!!ft_isprint(c) != !!isprint(c))
			ok[3] = 0;
		if (ft_toupper(c) != toupper(c))
			ok[4] = 0;
		if (ft_tolower(c) != tolower(c))
			ok[5] = 0;
	}
	for (c = 0; c < 128; c++)
		if (!ft_isascii(c))
			ok[6] = 0;
	if (ft_isascii(128) || ft_isascii(-1) || ft_isascii(300))
		ok[6] = 0;
	check("isalpha", ok[0]);
	check("isdigit", ok[1]);
	check("isalnum", ok[2]);
	check("isprint", ok[3]);
	check("toupper", ok[4]);
	check("tolower", ok[5]);
	check("isascii", ok[6]);
}

static void	test_str(void)
{
	char		buf[20];
	const char	*big = "hello world";
	int			ok;

	/* strlen */
	check("strlen", ft_strlen("") == strlen("")
		&& ft_strlen("a") == strlen("a")
		&& ft_strlen("hello world") == strlen("hello world"));

	/* strchr */
	check("strchr", ft_strchr(big, 'o') == strchr(big, 'o')
		&& ft_strchr(big, 'z') == strchr(big, 'z')
		&& ft_strchr(big, 'h') == strchr(big, 'h')
		&& ft_strchr(big, '\0') == strchr(big, '\0')
		&& ft_strchr(big, 'o' + 256) == strchr(big, 'o' + 256));

	/* strrchr */
	check("strrchr", ft_strrchr(big, 'o') == strrchr(big, 'o')
		&& ft_strrchr(big, 'z') == strrchr(big, 'z')
		&& ft_strrchr(big, 'h') == strrchr(big, 'h')
		&& ft_strrchr(big, '\0') == strrchr(big, '\0'));

	/* strncmp */
	check("strncmp", sign(ft_strncmp("abc", "abd", 3)) == sign(strncmp("abc", "abd", 3))
		&& sign(ft_strncmp("abc", "abd", 2)) == sign(strncmp("abc", "abd", 2))
		&& sign(ft_strncmp("abc", "abc", 10)) == sign(strncmp("abc", "abc", 10))
		&& sign(ft_strncmp("abc", "ab", 3)) == sign(strncmp("abc", "ab", 3))
		&& sign(ft_strncmp("", "a", 1)) == sign(strncmp("", "a", 1))
		&& sign(ft_strncmp("a", "b", 0)) == sign(strncmp("a", "b", 0))
		&& sign(ft_strncmp("\200", "\100", 1)) == sign(strncmp("\200", "\100", 1))
		&& sign(ft_strncmp("ab\0cd", "ab\0xy", 5)) == sign(strncmp("ab\0cd", "ab\0xy", 5)));

	/* strlcpy */
	ok = 1;
	memset(buf, 'X', sizeof(buf));
	if (ft_strlcpy(buf, "hello", 10) != 5 || strcmp(buf, "hello") != 0)
		ok = 0;
	memset(buf, 'X', sizeof(buf));
	if (ft_strlcpy(buf, "hello", 3) != 5 || strcmp(buf, "he") != 0)
		ok = 0;
	memset(buf, 'X', sizeof(buf));
	if (ft_strlcpy(buf, "hello", 0) != 5 || buf[0] != 'X')
		ok = 0;
	memset(buf, 'X', sizeof(buf));
	if (ft_strlcpy(buf, "", 5) != 0 || buf[0] != '\0')
		ok = 0;
	check("strlcpy", ok);

	/* strlcat */
	ok = 1;
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "ab");
	if (ft_strlcat(buf, "cde", 10) != 5 || strcmp(buf, "abcde") != 0)
		ok = 0;
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "ab");
	if (ft_strlcat(buf, "cde", 4) != 5 || strcmp(buf, "abc") != 0)
		ok = 0;
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "ab");
	if (ft_strlcat(buf, "cde", 2) != 5 || strcmp(buf, "ab") != 0)
		ok = 0;
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "ab");
	if (ft_strlcat(buf, "cde", 0) != 3 || strcmp(buf, "ab") != 0)
		ok = 0;
	check("strlcat", ok);

	/* strnstr */
	ok = 1;
	{
		const char	*h = "hello";

		if (ft_strnstr(h, "ll", 5) != h + 2)
			ok = 0;
		if (ft_strnstr(h, "ll", 3) != NULL)
			ok = 0;
		if (ft_strnstr(big, "world", 11) != big + 6)
			ok = 0;
		if (ft_strnstr(big, "world", 10) != NULL)
			ok = 0;
		if (ft_strnstr(big, "", 5) != big)
			ok = 0;
		if (ft_strnstr(big, "xyz", 11) != NULL)
			ok = 0;
		if (ft_strnstr(big, "o", 0) != NULL)
			ok = 0;
	}
	check("strnstr", ok);

	/* atoi */
	check("atoi", ft_atoi("42") == atoi("42")
		&& ft_atoi("-42") == atoi("-42")
		&& ft_atoi("  +7") == atoi("  +7")
		&& ft_atoi("\t\n 12") == atoi("\t\n 12")
		&& ft_atoi("abc") == atoi("abc")
		&& ft_atoi("0") == atoi("0")
		&& ft_atoi("12ab") == atoi("12ab")
		&& ft_atoi("2147483647") == atoi("2147483647")
		&& ft_atoi("-2147483648") == atoi("-2147483648")
		&& ft_atoi("+-5") == atoi("+-5")
		&& ft_atoi("") == atoi(""));
}

static void	test_mem(void)
{
	char	a[10];
	char	b[10];
	char	m1[] = "ABCDEF";
	char	m2[] = "ABCDEF";
	char	m3[] = "ABCDEF";
	char	m4[] = "ABCDEF";
	char	z[] = "ab\0cd";
	int		ok;

	/* memset */
	memset(a, 1, 10);
	memset(b, 1, 10);
	memset(a, 'A', 10);
	ft_memset(b, 'A', 10);
	ok = memcmp(a, b, 10) == 0;
	memset(a, 'B', 5);
	ft_memset(b, 'B', 5);
	ok = ok && memcmp(a, b, 10) == 0;
	memset(a, 256 + 'C', 4);
	ft_memset(b, 256 + 'C', 4);
	ok = ok && memcmp(a, b, 10) == 0;
	ok = ok && ft_memset(b, 0, 0) == b;
	check("memset", ok);

	/* bzero */
	memset(a, 'Z', 10);
	memset(b, 'Z', 10);
	memset(a, 0, 6);
	ft_bzero(b, 6);
	ok = memcmp(a, b, 10) == 0;
	ft_bzero(b, 0);
	ok = ok && memcmp(a, b, 10) == 0;
	check("bzero", ok);

	/* memcpy */
	memset(a, 0, 10);
	memset(b, 0, 10);
	memcpy(a, "hello", 6);
	ok = ft_memcpy(b, "hello", 6) == b && memcmp(a, b, 10) == 0;
	ft_memcpy(b, "XXXX", 0);
	ok = ok && memcmp(a, b, 10) == 0;
	check("memcpy", ok);

	/* memmove: overlap in both directions */
	memmove(m1 + 2, m1, 4);
	ok = ft_memmove(m2 + 2, m2, 4) == m2 + 2 && strcmp(m1, m2) == 0;
	memmove(m3, m3 + 2, 4);
	ft_memmove(m4, m4 + 2, 4);
	ok = ok && strcmp(m3, m4) == 0;
	ok = ok && strcmp(m1, "ABABCD") == 0 && strcmp(m3, "CDEFEF") == 0;
	check("memmove", ok);

	/* memchr */
	ok = ft_memchr("hello", 'l', 5) == memchr("hello", 'l', 5);
	ok = ok && ft_memchr("hello", 'o', 5) == memchr("hello", 'o', 5);
	ok = ok && ft_memchr("hello", 'o', 4) == NULL;
	ok = ok && ft_memchr("hello", 'z', 5) == NULL;
	ok = ok && ft_memchr("hello", 'h', 0) == NULL;
	ok = ok && ft_memchr(z, 'd', 5) == z + 4;
	ok = ok && ft_memchr(z, 0, 5) == z + 2;
	ok = ok && ft_memchr("hello", 'l' + 256, 5) == memchr("hello", 'l', 5);
	check("memchr", ok);

	/* memcmp */
	ok = sign(ft_memcmp("abc", "abd", 3)) == sign(memcmp("abc", "abd", 3));
	ok = ok && ft_memcmp("abc", "abd", 2) == 0;
	ok = ok && ft_memcmp("abc", "abc", 3) == 0;
	ok = ok && ft_memcmp("abc", "abd", 0) == 0;
	ok = ok && sign(ft_memcmp("\200", "\100", 1)) == sign(memcmp("\200", "\100", 1));
	ok = ok && sign(ft_memcmp("ab\0cd", "ab\0xy", 5)) == sign(memcmp("ab\0cd", "ab\0xy", 5));
	check("memcmp", ok);
}

static void	test_part2(void)
{
	char	s1[] = "hello";
	char	s2[] = "abcdefghijkl";

	ft_striteri(s1, to_upper_cb);
	ft_striteri(s2, index_cb);
	ft_striteri(NULL, to_upper_cb);
	ft_striteri(s1, NULL);
	check("striteri", strcmp(s1, "HELLO") == 0
		&& strcmp(s2, "012345678901") == 0);
}

int	main(void)
{
	test_ctype();
	test_str();
	test_mem();
	test_part2();
	if (g_fail == 0)
		printf("\nAll tests passed.\n");
	else
		printf("\n%d test(s) failed.\n", g_fail);
	return (g_fail != 0);
}