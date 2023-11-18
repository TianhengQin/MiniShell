/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:40:34 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/18 10:33:36 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_s = sig - 129;
}

// void	sig_newline(int sig)
// {
// 	write(1, "\n", 1);
// 	g_s = sig;
// }

void	set_signal_b(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	rm_signal();
	sa.sa_handler = ctrl_c;
	sb.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
}

// void	sig_quit(int sig)
// {
// 	fprint(2, "Quit: %d\n", sig);
// 	g_s = sig;
// }

void	set_signal_a(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	sa.sa_handler = SIG_IGN;
	sb.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
}
