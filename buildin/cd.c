/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:26:10 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/17 04:42:37 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_pwd(t_sh *sh)
{
	char	*dir;

	if (sh->pwd)
		free(sh->pwd);
	dir = malloc(1024);
	if (!dir)
		return ;
	getcwd(dir, 1024);
	sh->pwd = sdup(dir);
	free(dir);
}

int	go_to(t_sh *sh, char *cs)
{
	char	*dir;
	int		dd;

	if (cs[0] == 0)
		return (0);
	if (cs[0] == '/')
		dir = sdup(cs);
	else
	{
		dir = sjoin(sh->pwd, "/");
		dir = sjoinf1(dir, cs);
	}
	dd = chdir(dir);
	if (dd)
	{
		free(dir);
		perror("cd");
		sh->exit_c = 1;
		return (1);
	}
	set_pwd(sh);
	free(dir);
	return (0);
}

void	run_cd(t_sh *sh, char **cs)
{
	char	*tmp;

	if (cs[1] && cs[2])
	{
		fprint(2, "cd: string not in pwd: %s\n", cs[1]);
		sh->exit_c = 1;
		return ;
	}
	tmp = sdup(sh->pwd);
	if (!cs[1] || !cs[1][0])
	{
		go_to(sh, sh->home);
	}
	else
	{
		if (go_to(sh, cs[1]))
		{
			free(tmp);
			return ;
		}
	}
	free(sh->odpwd);
	sh->odpwd = tmp;
	set_env_r(sh);
}
