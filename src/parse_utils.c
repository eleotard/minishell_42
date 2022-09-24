/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:39:22 by elpastor          #+#    #+#             */
/*   Updated: 2022/09/24 18:41:02 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnumplus(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '$' || c == '?')
		return (1);
	return (0);
}

void	del_unused_quot_plus(t_token *tmp)
{
	while (tmp)
	{
		if (tmp->type == word || tmp->type == fout)
		{
			tmp->str = del_unused_quot(tmp->str);
		}
		tmp = tmp->next;
	}
}
