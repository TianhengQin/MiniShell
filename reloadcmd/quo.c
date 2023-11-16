/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:41:25 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 20:32:19 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	isin_quo(char c, int *in_quo)
{
	if (c == '\'')
	{
		if (*in_quo == 0)
			*in_quo = 1;
		else if (*in_quo == 1)
			*in_quo = 0;
	}
	else if (c == '"')
	{
		if (*in_quo == 0)
			*in_quo = 2;
		else if (*in_quo == 2)
			*in_quo = 0;
	}
	else if (c == -1)
	{
		if (*in_quo == 0)
			*in_quo = -3;
		else
			*in_quo = -(*in_quo);
	}
}

void	write_exit(t_sh *sh, char *re, int *j)
{
	int	exit;

	exit = sh->exit_c;
	if (exit / 100)
		re[(*j)++] = exit / 100 + 48;
	if (exit / 100 || exit % 100 / 10)
		re[(*j)++] = exit % 100 / 10 + 48;
	exit = exit % 10;
	re[(*j)++] = exit + 48;
}

void	write_env(char *re, int *j, char *ev)
{
	char	*tmp;
	int		i;

	re[(*j)++] = -1;
	i = 0;
	tmp = sdup(ev);
	// tmp = dequo(tmp);
	// fprint(2, "%s\n", tmp);
	while (tmp[i])
	{
		re[(*j)++] = tmp[i++];
	}
	free(tmp);
	re[(*j)++] = -1;
}

int	write_dolor(char *c, t_sh *sh, char *re, int *j)
{
	int		len;
	char	tmp;
	int		f;
	int		i;

	if (c[0] == '?')
	{
		write_exit(sh, re, j);
		return (1);
	}
	len = 0;
	while (is_aphnum(c[len]))
		len++;
	tmp = c[len];
	c[len] = '=';
	f = find(sh->env, c);
	c[len] = tmp;
	i = len + 1;
	if (f >= 0)
	{
		// while (sh->env[f][i])
		// 	re[(*j)++] = sh->env[f][i++];
		write_env(re, j, &sh->env[f][i]);
	}
	return (len);
}

char	*quo(t_sh *sh, char *c)
{
	int		i;
	int		in_quo;
	char	*re;
	int		j;

	j = 0;
	re = malloc(1024);
	i = -1;
	in_quo = 0;
	while (c[++i])
	{
		if (c[i] == '\'' || c[i] == '"')
			isin_quo(c[i], &in_quo);
		if (c[i] == '$' && in_quo != 1
			&& (is_apha(c[i + 1]) || c[i + 1] == '?'
				|| ((c[i + 1] == '"' || c[i + 1] == '\'') && !in_quo)))
			i += write_dolor(&c[i + 1], sh, re, &j);
		else
			re[j++] = c[i];
	}
	re[j] = 0;
	free(c);
	re = sdupf(re);
	// fprint(2, "%s\n", re);
	return (re);
}
