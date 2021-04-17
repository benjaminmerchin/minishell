#include "../includes/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}


void	ft_putstr_fd(char *s, int fd)
{
	write(fd, (unsigned char *)s, ft_strlen(s));
}

char	*ft_strdup(char *s)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s) + 1;
	if (!(res = malloc(sizeof(char) * len)))
		return (NULL);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

int		ft_strncmp(char *s1, char *s2, int n)
{
	int i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i + 1 < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
