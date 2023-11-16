/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:25:40 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 02:32:05 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sort_env(t_sh *sh, int *ix, int l)
{
	int	i;
	int	sorted;

	i = 0;
	sorted = 1;
	while (sorted)
	{
		i = 0;
		sorted = 0;
		while (i < l - 2)
		{
			if (sncmp(sh->env[ix[i]], sh->env[ix[i + 1]], 2147483647) > 0)
			{
				sorted = ix[i];
				ix[i] = ix[i + 1];
				ix[i + 1] = sorted;
				sorted = 1;
			}
			i++;
		}
	}
}

int	is_none(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
	{
		i++;
	}
	i++;
	if (env[i])
		return (0);
	else
		return (1);
}

void	show_exp(t_sh *sh)
{
	int	*ix;
	int	l;
	int	i;

	i = -1;
	l = 0;
	while (sh->env[l])
		l++;
	ix = malloc((l - 1) * sizeof(int));
	if (!ix)
		return ;
	while (++i < l - 1)
		ix[i] = i;
	sort_env(sh, ix, l);
	i = 0;
	while (i < l - 1)
	{
		if (is_none(sh->env[ix[i]]))
			fprint(1, "%s''\n", sh->env[ix[i++]]);
		else
			fprint(1, "%s\n", sh->env[ix[i++]]);
	}
	free(ix);
	sh->exit_c = 0;
}

char	*prase_exp(char *cs)
{
	char	*re;
	int		i;
	int		f;

	i = 0;
	f = 0;
	while (cs[i])
	{
		if (cs[i] == '=')
		{
			f = 1;
			break ;
		}
		i++;
	}
	if (f == 0)
		re = sjoin(cs, "=");
	else
		re = sdup(cs);
	return (re);
}

void	run_export(t_sh *sh, char **cs)
{
	char	*tofind;
	int		i;

	sh->exit_c = 0;
	if (!cs[1])
	{
		show_exp(sh);
		return ;
	}
	i = 0;
	while (cs[++i])
	{
		if (valid_exp(cs[i]))
		{
			fprint(2, "export: `%s': not a valid identifier\n", cs[i]);
			sh->exit_c = 1;
			continue ;
		}
		tofind = prase_exp(cs[i]);
		env_append(sh, tofind);
		free(tofind);
	}
}
