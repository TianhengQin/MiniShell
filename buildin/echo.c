/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:44:47 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 02:11:54 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	opt_n(char *c)
{
	int	i;

	if (c[0] != '-')
		return (0);
	if (c[1] != 'n')
		return (0);
	i = 2;
	while (c[i])
	{
		if (c[i] != 'n')
			return (0);
		i++;
	}
	return ('n');
}

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
	while (cs[i] && opt_n(cs[i]))
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
	else if (!opt_n(cs[1]))
		echo(cs);
	else
		echo_n(cs);
	sh->exit_c = 0;
}
