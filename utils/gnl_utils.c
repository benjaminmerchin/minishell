/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:50:26 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 00:50:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strlen(char *s)
{
	unsigned int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_joinofgnl(char *s1, char *s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;

	if ((!s1 && !s2) || !(res = malloc(sizeof(*res) * \
	(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	len = ft_strlen(s2);
	while (j < len)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}
