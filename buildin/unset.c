/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:38:51 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 02:48:55 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	valid_unset(char *s)
{
	int	i;

	if (is_apha(s[0]) == 0)
		return (1);
	i = 0;
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
	int		j;

	sh->exit_c = 0;
	if (!cs[1])
	{
		fprint(2, "unset: not enough arguments\n");
		sh->exit_c = 1;
		return ;
	}
	j = 0;
	while (cs[++j])
	{
		if (valid_unset(cs[j]))
		{
			fprint(2, "unset: `%s': not a valid identifier\n", cs[j]);
			sh->exit_c = 1;
			continue ;
		}
		cs[j] = sjoinf1(cs[j], "=");
		i = find(sh->env, cs[j]);
		if (i >= 0)
			env_delete(sh, i);
	}
}
