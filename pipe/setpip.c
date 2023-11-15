/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setpip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:45:11 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/15 07:40:50 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	close_pip(t_sh *sh, int j)
{
	int	i;

	i = 0;
	while (sh->pip[2 * i] != -1)
	{
		if (i != j && i != j - 1)
		{
			close(sh->pip[2 * i]);
			close(sh->pip[2 * i + 1]);
		}
		i++;
	}
}

void	set_pip(t_sh *sh)
{
	int	l;
	int	i;

	l = len3(sh->iof);
	sh->pip = malloc(l * 2 * sizeof(int));
	i = 0;
	while (i < l - 1)
	{
		if (pipe(&sh->pip[2 * i]) == -1)
		{
			free(sh->pip);
			return ;
		}
		i++;
	}
	sh->pip[2 * i] = -1;
	sh->pip[2 * i + 1] = -1;
}
