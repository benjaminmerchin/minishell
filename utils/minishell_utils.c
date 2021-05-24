#include "../includes/minishell.h"

void	ft_title(void)
{
	char	pwdname[1024];

	ft_putstr_fd("\033[035m", 1);
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd("\033[036m ", 1);
	if (getcwd(pwdname, sizeof(pwdname)) == NULL)
		return ;
	ft_putstr_fd(pwdname, 1);
	ft_putstr_fd("> \033[0m", 1);
}

void	ft_appendbuffer(t_a *a, int k)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(a->h[a->nav]) + k + 1));
	if (!str)
		ft_exit_clean(a, "Error\nMalloc failed in appendchar\n");
	i = 0;
	while (a->h[a->nav] && a->h[a->nav][i])
	{
		str[i] = a->h[a->nav][i];
		i++;
	}
	j = 0;
	while (j < k)
	{
		str[i] = a->buff[j];
		i++;
		j++;
	}
	str[i] = 0;
	if (a->h[a->nav])
		free(a->h[a->nav]);
	a->h[a->nav] = str;
}

void	ft_store_env_in_lst(t_a *a)
{
	int		i;
	t_list	*lst;
	t_list	*temp;
	char	*char_temp;

	i = 1;
	char_temp = ft_strdup(a->env[0]);
	lst = ft_lstnew(char_temp);
	while (a->env[i - 1] && a->env[i])
	{
		if (ft_strncmp("PWD=", a->env[i], 4) == 0)
			a->len_head += ft_strlen(a->env[i] + 4);
		char_temp = ft_strdup(a->env[i]);
		temp = ft_lstnew(char_temp);
		ft_lstadd_back(&lst, temp);
		i++;
	}
	a->lst_env = lst;
}

void	ft_dedoublonne(t_a *a)
{
	if (a->nline < 2)
		return ;
	if (ft_strncmp(a->h[a->nline - 1], a->h[a->nline - 2], \
	ft_strlen(a->h[a->nline - 1])) == 0)
	{
		if (a->h[a->nline - 1])
		{
			a->h[a->nline - 1][0] = 0;
			free(a->h[a->nline - 1]);
			a->h[a->nline - 1] = NULL;
		}
		a->nline--;
		return ;
	}
}

void	ft_newline(t_a *a)
{
	if (a->line && !DEBUG)
		free(a->line);
	a->line = ft_strdup(a->h[a->nav]);
	if (!a->h[a->nav][0])
	{
		if (a->h[a->nline - 1])
		{
			free(a->h[a->nline - 1]);
			a->h[a->nline - 1] = NULL;
		}
		a->nline--;
		return ;
	}
	else if (a->nav == a->nline - 1)
	{
		ft_dedoublonne(a);
		return ;
	}
	else
	{
		if (a->h[a->nline - 1])
			free(a->h[a->nline - 1]);
		a->h[a->nline - 1] = ft_strdup(a->h[a->nav]);
		ft_dedoublonne(a);
	}
}
