#include "../includes/minishell.h"

static char		*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
	}
	return (str);
}

static size_t	ft_intlen(int nb)
{
	size_t	i;

	i = 1;
	while (nb /= 10)
		++i;
	return (i);
}

char			*ft_itoa(int n)
{
	long		nb;
	size_t		nlen;
	size_t		i;
	char		*res;

	nb = n;
	i = -1;
	if (n < 0)
		nb = -nb;
	nlen = ft_intlen(n);
	res = malloc(nlen + 1 + (n < 0) * sizeof(char));
	if (!res)
		return (NULL);
	while (++i <= nlen)
		res[i] = 0;
	i = 0;
	res[i] = '0';
	while (nb)
	{
		res[i++] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		res[i++] = '-';
	return (ft_strrev(res));
}