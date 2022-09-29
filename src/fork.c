/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:03:32 by elpastor          #+#    #+#             */
/*   Updated: 2022/09/29 23:08:53 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_cmd *cmd, t_cmd *tmp, const char *pathname)
{
	char	**argv;
	char	**env;
	int		nb_of_arg;

	env = get_exec_env();
	if (!env)
		exit_free(cmd, "\nERROR MALLOC ENV\n", 'c', 1);
	nb_of_arg = find_nb_of_args(tmp);
	if (nb_of_arg >= 1)
	{
		argv = get_exec_args(tmp, nb_of_arg);
		if (!argv)
			free_tabs_exit_free(cmd, env, argv, "ERROR MALLOC ARGS\n");
		if (!strcmp(pathname, argv[0]))
			pathname = argv[0];
		ctfree(cmd, NULL, 'c', get_exit());
		if (execve(pathname, argv, env) == -1)
			exit(127);
	}
}

void	determine_exe_type(t_cmd *cmd, t_cmd *tmp, char *path)
{
	check_exceptions_exec(tmp);
	if (!is_built(tmp) && !find_slash(tmp))
	{
		path = look_for_path(tmp);
		if (!path)
		{
			if (tmp->arg)
				print_err("command not found: ", tmp->arg->str, NULL);
			exit_free(cmd, NULL, 'c', 127);
		}
		exec(cmd, tmp, path);
	}
	else if (!is_built(tmp) && find_slash(tmp))
	{
		if (access(tmp->arg->str, X_OK) == -1)
		{
			print_err("command not found: ", tmp->arg->str, NULL);
			exit_free(cmd, NULL, 'c', 127);
		}
		check_file_type(tmp, tmp->arg->str);
		exec(cmd, tmp, tmp->arg->str);
	}
}

void	single_cmd_handler(t_cmd *cmd)
{
	reset_default_signals();
	if (cmd->fdin != 0)
		dup2(cmd->fdin, 0);
	if (cmd->fdout != 1)
		dup2(cmd->fdout, 1);
	close_all_fds(cmd, 1);
	determine_exe_type(cmd, cmd, NULL);
}

void	do_multi_pipe_or_single_non_built(t_cmd *cmd, int *res)
{
	if (get_cmd_size(cmd) > 1)
		*res = ft_multi_pipe(cmd);
	else
	{
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			*res = 2;
			return ;
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (cmd->pid == 0)
			single_cmd_handler(cmd);
		else
		{
			close_all_fds(cmd, 1);
			check_children_status(cmd, cmd, res);
		}
	}
}

void	*parent(t_cmd *cmd, int res)
{
	if (!is_exe(cmd) && cmd->arg && cmd->arg->str && get_cmd_size(cmd) == 1)
	{
		print_err("command not found: ", cmd->arg->str, NULL);
		return (ctfree(cmd, NULL, 'c', 127), NULL);
	}
	if (!cmd->arg)
		return (close_all_fds(cmd, 1), ctfree(cmd, NULL, 'c', get_exit()),
			NULL);
	if (is_built(cmd) && get_cmd_size(cmd) == 1)
	{
		close_all_fds(cmd, 0);
		exec_built(cmd, cmd);
		return (ctfree(cmd, NULL, 'c', get_exit()), NULL);
	}
	else
	{
		do_multi_pipe_or_single_non_built(cmd, &res);
		return (ctfree(cmd, NULL, 'c', res), NULL);
	}
	return (ctfree(cmd, NULL, 'c', res), NULL);
}
