/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:38:51 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/14 21:59:43 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	valid_unset(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '_')
			continue ;
		else if (s[i] >= 'a' && s[i] <= 'z')
			continue ;
		else if (s[i] >= 'A' && s[i] <= 'Z')
			continue ;
		else if (s[i] >= '0' && s[i] <= '9')
			continue ;
		return (1);
	}
	return (0);
}

void	run_unset(t_sh *sh, char **cs)
{
	int		i;

	if (!cs[1])
	{
		fprint(2, "unset: not enough arguments\n");
		sh->exit_c = 1;
		return ;
	}
	if (valid_unset(cs[1]))
	{
		fprint(2, "unset: `%s': not a valid identifier\n", cs[1]);
		sh->exit_c = 1;
		return ;
	}
	cs[1] = sjoinf1(cs[1], "=");
	i = find(sh->env, cs[1]);
	sh->exit_c = 0;
	if (i < 0)
		return ;
	env_delete(sh, i);
}
