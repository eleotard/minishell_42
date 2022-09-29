/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:36:25 by eleotard          #+#    #+#             */
/*   Updated: 2022/09/29 21:47:34 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	catch_sigint(int sig)
{
	(void)sig;
	if (write(1, "\n", 1) == -1)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	handler(130, NULL, "?", NULL);
}

void	reset_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

void	catch_signals(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	here_handler_sigint(int sig)
{
	(void)sig;
	if (write(1, "\n", 1) == -1)
		return ;
	close(0);
	handler(130, NULL, "?", NULL);
}
