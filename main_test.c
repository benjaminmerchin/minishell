# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include <curses.h>
# include <term.h>

int		ft_strlen(char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
void	ft_putchar(char c)
{
	write(1, &c, 1);
}
void	ft_putnbr(int n)
{
	long nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
	}
	else
		ft_putchar(nbr + '0');
}
void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

int main(void)
{
	int i = 0;
	char *str = "abc\"defg";
	printf("Longueur du string : %lu\n", strlen(str));
	while (str[i])
	{
		putchar(str[i]);
		putchar('\n');
		i++;
	}
	putchar('\'');
	putchar('\n');
	ft_putstr("----------\n");
	ft_putnbr('"');
	putchar('\n');
	ft_putnbr(str[3]);
	putchar('\n');
	return (0);
}
