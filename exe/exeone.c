/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:58 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/17 00:12:17 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*rltv_pth(char *pwd, char *cs)
{
	char	*rpth;

	rpth = sjoin(pwd, cs);
	if (access(rpth, F_OK | X_OK) == 0)
		return (rpth);
	free(rpth);
	return (0);
}

char	*get_pth(char *pwd, char **evpth, char *cs)
{
	char	*right_path;
	char	*cmd;
	int		i;

	right_path = 0;
	if (access(cs, F_OK | X_OK) == 0)
		return (sdup(cs));
	if (cs[0] == '.')
		return (rltv_pth(pwd, cs));
	cmd = sjoin("/", cs);
	i = -1;
	while (evpth && evpth[++i])
	{
		right_path = sjoin(evpth[i], cmd);
		if (access(right_path, F_OK | X_OK) == 0)
			break ;
		free(right_path);
		right_path = 0;
	}
	free(cmd);
	return (right_path);
}

void	run_exe(t_sh *sh, char **cs)
{
	char	*pth;
	pid_t	m_pid;
	int		ext;

	m_pid = fork();
	if (m_pid == 0)
	{
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
		free_sh(sh);
		free2(cs);
		perror("minishell");
		exit(126);
	}
	waitpid(m_pid, &ext, 0);
	sh->exit_c = ext / 256;
}

char	is_buin(char *c)
{
	if (sncmp(c, "cd", 3) == 0)
		return (1);
	else if (sncmp(c, "echo", 5) == 0)
		return (1);
	else if (sncmp(c, "pwd", 4) == 0)
		return (1);
	else if (sncmp(c, "export", 7) == 0)
		return (1);
	else if (sncmp(c, "unset", 6) == 0)
		return (1);
	else if (sncmp(c, "env", 4) == 0)
		return (1);
	else if (sncmp(c, "exit", 5) == 0)
		return (1);
	return (0);
}

void	exe_cmd(t_sh *sh, char **cs)
{
	sh->exe = 1;
	crt_hirdoc(sh);
	redir(sh, sh->iof[0]);
	if (!cs[0] || sh->exe == 0)
	{
		reset_io(sh);
		return ;
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
		run_exe(sh, cs);
	reset_io(sh);
}
