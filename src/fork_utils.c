/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:31:00 by elsie             #+#    #+#             */
/*   Updated: 2022/09/29 22:50:56 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exceptions_exec(t_cmd *cmd)
{
	if (!is_exe(cmd) && cmd->arg && cmd->arg->str)
	{
		print_err("command not found: ", cmd->arg->str, NULL);
		exit_free(cmd, NULL, 'c', 127);
	}
	if (!cmd->arg)
		exit_free(cmd, NULL, 'c', get_exit());
}

void	check_file_type(t_cmd *cmd, char *filestr)
{
	struct stat buf;
	
	stat(filestr, &buf);
	if (buf.st_mode != 0100000)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(filestr, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit_free(cmd, NULL, 'c', 126);
	}
		
}