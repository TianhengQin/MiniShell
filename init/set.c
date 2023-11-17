/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:30:12 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/17 03:34:42 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	find(char **str, char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[len] != '=')
		len++;
	len++;
	while (str[i])
	{
		if (sncmp(str[i], s, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	init_env(t_sh *sh)
{
	int		i;
	char	**re;

	i = 0;
	while (sh->env[i])
		i++;
	re = malloc((i + 1) * sizeof(char *));
	if (!re)
		return ;
	i = -1;
	while (sh->env[++i])
		re[i] = sdup(sh->env[i]);
	sh->env = re;
}

void	set_env(t_sh *shell)
{
	int		i;

	init_env(shell);
	i = find(shell->env, "PWD=");
	shell->pwd = sdup(shell->env[i] + 4);
	i = find(shell->env, "OLDPWD=");
	if (i >= 0)
		shell->odpwd = sdup(shell->env[i] + 7);
	else
		shell->odpwd = sdup(shell->env[find(shell->env, "PWD=")] + 4);
	shell->user = sdup(shell->env[find(shell->env, "USER=")] + 5);
	shell->home = sdup(shell->env[find(shell->env, "HOME=")] + 5);
	shell->evpth = ft_split(shell->env[find(shell->env, "PATH=")] + 5, ":");
	shell->runing = 1;
	if (find(shell->env, "SHLVL=") >= 0)
		shell->env[find(shell->env, "SHLVL=")][6]++;
	i = find(shell->env, "_=");
	free(shell->env[i]);
	shell->env[i] = sdup("_=/usr/bin/env");
	shell->exit_c = 0;
	shell->stdi = -1;
	shell->stdo = -1;
	shell->pip = 0;
}

/*
set env reverse
*/
void	set_env_r(t_sh *shell)
{
	int		i;
	char	*pwd;

	pwd = sjoin("PWD=", shell->pwd);
	i = find(shell->env, "PWD=");
	if (i >= 0)
	{
		free(shell->env[i]);
		shell->env[i] = sjoin("PWD=", shell->pwd);
	}
	else
		env_append(shell, pwd);
	free(pwd);
	pwd = sjoin("OLDPWD=", shell->odpwd);
	i = find(shell->env, "OLDPWD=");
	if (i >= 0)
	{
		free(shell->env[i]);
		shell->env[i] = sjoin("OLDPWD=", shell->odpwd);
	}
	else
		env_append(shell, pwd);
	free(pwd);
}

void	set_envpth(t_sh *sh)
{
	if (sh->evpth)
		free2(sh->evpth);
	if (find(sh->env, "PATH=") >= 0)
	{
		sh->evpth = ft_split(sh->env[find(sh->env, "PATH=")] + 5, ":");
	}
	else
		sh->evpth = 0;
}
