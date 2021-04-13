#include "../includes/minishell.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_strdup(const char *s)
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
