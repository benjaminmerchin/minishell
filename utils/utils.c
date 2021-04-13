#include "../includes/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
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
