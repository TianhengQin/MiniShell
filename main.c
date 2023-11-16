/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:31:37 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 06:13:21 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_dir(t_sh *shell)
{
	char	*a;
	int		i;

	i = 0;
	a = sjoinf1(sdup(shell->user), "@minish ");
	i = len(shell->pwd);
	while (shell->pwd[i] != '/')
		i--;
	if (sncmp(shell->pwd, shell->home, 2147483647))
	{
		if (len(shell->pwd) < len(shell->home))
			a = sjoinf1(a, &(shell->pwd[i]));
		else
			a = sjoinf1(a, &(shell->pwd[i + 1]));
	}
	else
		a = sjoinf1(a, "~");
	a = sjoinf1(a, " % ");
	return (a);
}

void	rcv_sig(t_sh *shell)
{
	if (g_s)
		shell->exit_c = 128 + g_s;
	g_s = 0;
}

void	run_shell(t_sh *shell)
{
	char	*p;
	char	*cmd;
	char	***css;

	while (shell->runing)
	{
		set_signal_b();
		p = get_dir(shell);
		cmd = readline(p);
		rcv_sig(shell);
		free(p);
		set_signal_a();
		if (!cmd)
			break ;
		if (cmd[0])
			add_history(cmd);
		css = all_cmd(shell, cmd);
				// fprint(2, "cmd:%s\n", cmd);
		if (!check(cmd, css, shell))
		{
			// printf("kein problem\n");
			// printf("---------------------------\n");
			exe_all(shell, css);
		}
		rcv_sig(shell);
		set_envpth(shell);
		free_cmd(cmd, css, shell);
			// fprint(2, "exit\n");
	}
	printf("\n[Process completed]\n\n");
}

int	all(char **env)
{
	t_sh	sh;

	sh.env = env;
	set_env(&sh);
	run_shell(&sh);
	free_sh(&sh);
	return (sh.exit_c);
}

int	main(int argi, char **argv, char **env)
{
	int	exit;

	argi = 0;
	argv = 0;
	exit = all(env);
	// system("leaks minishell");
	return (exit);
}
