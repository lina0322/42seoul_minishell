#include "minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*uc;

	uc = b;
	while (len > 0)
	{
		*uc++ = (unsigned char)c;
		len--;
	}
	return (b);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void		*ret;
	char		*cdst;
	const char	*csrc;

	if (!dst && !src)
		return (0);
	ret = dst;
	cdst = (char *)dst;
	csrc = (char *)src;
	while (n--)
		*cdst++ = *csrc++;
	return (ret);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (!(ret = malloc(size * count)))
		return (0);
	ft_memset(ret, 0, size * count);
	return (ret);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	ft_memcpy(ret, s1, len);
	ret[len] = 0;
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	size_t			i;
	size_t			s_size;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	s_size = ft_strlen(s);
	if (s_size <= start)
		return (ft_strdup(""));
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len && i + start < s_size)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int ft_strlen(const char *s)
{
	int i = 0;
	while(s[i])
	{
		i++;
	}
	return i;
}
