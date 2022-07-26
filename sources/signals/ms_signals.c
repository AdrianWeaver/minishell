/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:09:13 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/26 16:49:05 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	ft_my_magic_handler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		(void)signum;
	}
}

void	ft_my_magic_handler_not_interactive(int signum)
{
	ft_set_term_behaviour();
	if (signum == SIGINT)
	{
		ft_magic_malloc(FLUSH, 130, NULL);
		exit(130);
	}
	if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		ft_magic_malloc(FLUSH, 131, NULL);
		exit(131);
	}
}

void	ft_ignore_signal(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_handler = ft_ignore_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, 0);
	sigaction(SIGQUIT, &action, 0);
}

void	ft_signal_catching(void)
{
	struct sigaction	action;
	int					interactive_or_not;

	interactive_or_not = ft_is_interactive();
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (interactive_or_not == INTERACTIVE)
	{
		action.sa_handler = &ft_my_magic_handler_interactive;
		sigaction(SIGINT, &action, 0);
		sigaction(SIGQUIT, &action, 0);
	}
	else if (interactive_or_not == NOT_INTERACTIVE)
	{
		action.sa_handler = &ft_my_magic_handler_not_interactive;
		sigaction(SIGINT, &action, 0);
		sigaction(SIGQUIT, &action, 0);
	}
}
