/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exepip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:22:58 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/15 20:57:30 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	run_one(t_sh *sh, char **cs)
{
	char	*pth;

	pth = get_pth(sh->pwd, sh->evpth, cs[0]);
	if (!pth)
	{
		if (cs[0][0] == '.' || cs[0][0] == '/')
			fprint(2, "minishell: %s: No such file or directory\n", cs[0]);
		else
			fprint(2, "minishell: %s: command not found\n", cs[0]);
		exit(127);
	}
	execve(pth, cs, sh->env);
	free_fail(sh, cs);
	perror("minishell");
	exit(126);
}

void	exe_one(t_sh *sh, char **cs, int i)
{
	sh->exe = 1;
	redir(sh, sh->iof[i]);
	if (!cs[0] || sh->exe == 0)
	{
		reset_io(sh);
		exit(sh->exit_c);
	}
	if (sncmp(cs[0], "cd", 3) == 0)
		run_cd(sh, cs);
	else if (sncmp(cs[0], "echo", 5) == 0)
		run_echo(sh, cs);
	else if (sncmp(cs[0], "pwd", 4) == 0)
		run_pwd(sh, cs);
	else if (sncmp(cs[0], "export", 7) == 0)
		run_export(sh, cs);
	else if (sncmp(cs[0], "unset", 6) == 0)
		run_unset(sh, cs);
	else if (sncmp(cs[0], "env", 4) == 0)
		run_env(sh, cs);
	else if (sncmp(cs[0], "exit", 5) == 0)
		run_exit(sh, cs);
	else
		run_one(sh, cs);
	exit(sh->exit_c);
}

void	one_fork(t_sh *sh, char **cs, int i, int len)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		fprint(2, "Error creating process\n");
	else if (pid == 0)
	{
		close_pip(sh, i);
		if (i > 0)
		{
			close(sh->pip[2 * (i - 1) + 1]);
			dup2(sh->pip[2 * (i - 1)], 0);
			close(sh->pip[2 * (i - 1)]);
		}
		if (i < len - 1)
		{
			close(sh->pip[2 * i]);
			dup2(sh->pip[2 * i + 1], 1);
			close(sh->pip[2 * i + 1]);
		}
		exe_one(sh, cs, i);
	}
	else
		sh->pidf = pid;
}

int	error_code(int ext)
{
	if (WIFSIGNALED(ext))
		return (128 + WTERMSIG(ext));
	else if (WIFEXITED(ext))
		return (WEXITSTATUS(ext));
	else
		return (ext);
}

void	exe_pip(t_sh *sh, char ***css)
{
	int	i;
	int	ext;
	int	pidf;

	sh->exit_c = 0;
	i = 0;
	crt_hirdoc(sh);
	sh->stdi = dup(0);
	sh->stdo = dup(1);
	set_pip(sh);
	while (css[i])
	{
		one_fork(sh, css[i], i, len3(css));
		i++;
	}
	close_pip(sh, -1);
	pidf = 0;
	while (pidf != -1)
	{
		pidf = waitpid(-1, &ext, 0);
		ext = error_code(ext);
		if (pidf == sh->pidf)
			sh->exit_c = ext;
	}
	reset_io(sh);
}
