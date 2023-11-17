/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setnoenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 04:02:42 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/17 04:55:10 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_no_env(t_sh *sh)
{
	sh->pwd = 0;
	set_pwd(sh);
	sh->env = malloc(4 * sizeof(char *));
	if (!sh->env)
		return ;
	sh->user = sdup("(x л x)");
	sh->home = sdup("");
	sh->evpth = 0;
	sh->runing = 1;
	sh->env[0] = sjoin("PWD=", sh->pwd);
	sh->odpwd = sdup(sh->pwd);
	sh->env[1] = sdup("SHLVL=1");
	sh->env[2] = sdup("_=/usr/bin/env");
	sh->env[3] = 0;
	sh->exit_c = 0;
	sh->stdi = -1;
	sh->stdo = -1;
	sh->pip = 0;
}
