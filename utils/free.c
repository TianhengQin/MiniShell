/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:22:25 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/15 20:58:34 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free2(char **cs)
{
	int	i;

	if (!cs)
		return ;
	i = 0;
	while (cs[i])
	{
		free(cs[i]);
		i++;
	}
	free(cs);
}

void	free3(char ***cs)
{
	int	i;

	if (!cs)
		return ;
	i = 0;
	while (cs[i])
	{
		free2(cs[i]);
		i++;
	}
	free(cs);
}

void	free_sh(t_sh *sh)
{
	free2(sh->env);
	free2(sh->evpth);
	free(sh->odpwd);
	free(sh->pwd);
	free(sh->user);
}

void	free_cmd(char *cmd, char ***css, t_sh *sh)
{
	unlink(HERE_DOC_NAME);
	free(cmd);
	free3(css);
	free3(sh->iof);
	if (sh->pip)
	{
		free(sh->pip);
		sh->pip = 0;
	}
}

void	free_fail(t_sh *sh, char **cs)
{
	free_sh(sh);
	free3(sh->iof);
	free(sh->pip);
	sh->pip = 0;
	free2(cs);
}
