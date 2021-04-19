/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strlenn(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

char	*free_null(char *s1)
{
	free(s1);
	return (NULL);
}

int		free_int(char **line)
{
	free(*line);
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2, t_struct *data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlenn(s2) + 1))))
		return (free_null(s1));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\n' && s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
		data->curs += 1;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

int		get_next_line2(int fd, char **line, t_struct *data)
{
	while (data->ret > 0)
	{
		if (ft_strlen(data->buff + data->curs) !=
		ft_strlenn(data->buff + data->curs))
		{
			*line = ft_strjoin(*line, data->buff + data->curs, data);
			if (*line == NULL)
				return (-1);
			data->curs += 1;
			return (1);
		}
		if (data->curs < data->ret)
		{
			*line = ft_strjoin(*line, data->buff + data->curs, data);
			if (*line == NULL)
				return (-1);
		}
		data->ret = read(fd, data->buff, 4);
		if (data->ret < 0)
			return (free_int(line));
		data->buff[data->ret] = '\0';
		data->curs = 0;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_struct data;

	if (read(fd, data.buff, 0) < 0 || fd < 0 || fd > 10240 || line == NULL)
		return (-1);
	*line = (char *)malloc(sizeof(char));
	if (!*line)
		return (-1);
	*line[0] = '\0';
	if (ft_strlen(data.buff + data.curs) != ft_strlenn(data.buff + data.curs))
	{
		*line = ft_strjoin(*line, data.buff + data.curs, &data);
		if (*line == NULL)
			return (-1);
		data.curs += 1;
		return (1);
	}
	if (data.ret == 0)
	{
		data.ret = read(fd, data.buff, 4);
		if (data.ret < 0)
			return (free_int(line));
		data.buff[data.ret] = '\0';
	}
	return (get_next_line2(fd, line, &data));
}
