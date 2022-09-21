/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:37:42 by elpastor          #+#    #+#             */
/*   Updated: 2022/09/21 15:39:34 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built(t_cmd *cmd)
{
	if (!cmd || !cmd->arg || !cmd->arg->str)
		return (0);
	if (!strcmp(cmd->arg->str, "echo"))
		return (1);
	if (!strcmp(cmd->arg->str, "cd"))
		return (2);
	if (!strcmp(cmd->arg->str, "pwd"))
		return (3);
	if (!strcmp(cmd->arg->str, "export"))
		return (4);
	if (!strcmp(cmd->arg->str, "unset"))
		return (5);
	if (!strcmp(cmd->arg->str, "env"))
		return (6);
	if (!strcmp(cmd->arg->str, "exit"))
		return (7);
	return (0);
}

void	exec_built(t_cmd *cmd)
{
	if (is_built(cmd) == 1)
		ex_echo(cmd);
	else if (is_built(cmd) == 2)
		ex_cd(cmd, handler(3, NULL, "HOME", NULL));
	else if (is_built(cmd) == 3)
		ex_pwd(cmd);
	else if (is_built(cmd) == 4)
		ex_port(cmd);
	else if (is_built(cmd) == 5)
		ex_unset(cmd);
	else if (is_built(cmd) == 6)
		ex_env(cmd);
	else if (is_built(cmd) == 7)
		ex_it(cmd);
	if (cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != 1)
		close(cmd->fdout);
}

void	ex_echo(t_cmd *cmd)
{
	t_token	*arg;
	int		n;

	arg = cmd->arg->next;
	n = 0;
	while (arg)
	{
		if (arg->str && !ft_strncmp(arg->str, "-n", 2) && only_n(&arg->str[1]))
			n = 1;
		else
		{
			ft_putstr_fd(arg->str, cmd->fdout);
			if (arg->next)
				write(cmd->fdout, " ", 1);
		}
		arg = arg->next;
	}
	if (!n)
		write(cmd->fdout, "\n", 1);
}

void	ex_pwd(t_cmd *cmd)
{
	char	*s;
	char	buf[4096];

	s = getcwd(buf, 4096);
	if (s)
		ft_putstr_fd(s, cmd->fdout);
	write(cmd->fdout, "\n", 1);
}

void	ex_it(t_cmd *cmd)
{
	t_token			*arg;
	long long int	exit_status;
	int				atoi_err;

	if (!cmd->arg->next)
		exit_free(cmd, NULL, 'c', 0);
	if (cmd->arg->next->next)
	{
		print_err("exit: too many arguments", NULL, NULL);
		handler(1, NULL, "?", NULL);
		return ;
	}
	arg = cmd->arg->next;
	atoi_err = 0;
	exit_status = exit_atoi(arg->str, &atoi_err);
	if (atoi_err == 0)
		exit_free(cmd, "exit", 'c', exit_status);
	print_err("exit: ", arg->str, ": numeric argument required");
	exit_free(cmd, NULL, 'c', atoi_err);
}
