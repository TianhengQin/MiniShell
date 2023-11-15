/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:44:47 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/14 22:02:39 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	echo(char **cs)
{
	int	i;

	i = 1;
	while (cs[i])
	{
		if (i != 1)
			fprint(1, " ");
		fprint(1, "%s", cs[i]);
		i++;
	}
	fprint(1, "\n");
}

void	echo_n(char **cs)
{
	int	i;
	int	j;

	i = 2;
	while (cs[i] && sncmp(cs[i], "-n", 3) == 0)
		i++;
	j = i;
	while (cs[i])
	{
		if (i != j)
			fprint(1, " ");
		fprint(1, "%s", cs[i]);
		i++;
	}
}

void	run_echo(t_sh *sh, char **cs)
{
	(void)sh;
	if (!cs[1])
		fprint(1, "\n");
	else if (sncmp(cs[1], "-n", 3))
		echo(cs);
	else
		echo_n(cs);
	sh->exit_c = 0;
}
