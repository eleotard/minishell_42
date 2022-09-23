/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:23:53 by eleotard          #+#    #+#             */
/*   Updated: 2022/09/22 21:30:14 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hd_struct(t_hd *hd)
{
	hd->here = 0;
	hd->rdin = 0;
	hd->rdout = 0;
}

void	set_error_hd(t_token *token_tmp, t_cmd *cmd_tmp, t_hd *hd)
{
	file_err(token_tmp, cmd_tmp);
	if (cmd_tmp->fdin == -1)
		hd->rdin = 1;
	if (cmd_tmp->fdout == -1)
		hd->rdout = 1;
}
