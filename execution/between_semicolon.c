/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   between_semicolon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_between_semicolon(t_a *a, int *i)
{
	replace_var_env_until_next_separator(a, i);
	if (a->raw[*i].str != 0 && a->raw[*i + 1].str != 0 \
	&& a->raw[*i].type == '<')
		ft_attributefd(a, i, 0);
	else if (a->raw[*i].str != 0 && a->raw[*i + 1].str != 0 \
	&& a->raw[*i].type == '>')
		ft_attributefd(a, i, 1);
	else if (a->raw[*i].str != 0 && a->raw[*i + 1].str != 0 \
	&& a->raw[*i].type == '#')
		ft_attributefd(a, i, 2);
}
