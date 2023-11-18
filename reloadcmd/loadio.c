/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:04:51 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/18 10:46:36 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	write_hed(char *re, char *s, int *i, int *j)
{
	if (s[*i] == '<')
	{
		while ((s[*i] == '<') && (*i) < 2)
			(*i)++;
		re[(*j)++] = *i + 48;
		*i = 0;
		while ((s[*i] == '<') && (*i) < 2)
		{
			re[(*j)++] = s[*i];
			s[(*i)++] = ' ';
		}
	}
	else
	{
		while ((s[*i] == '>') && (*i) < 2)
			(*i)++;
		re[(*j)++] = *i + 48;
		*i = 0;
		while ((s[*i] == '>') && (*i) < 2)
		{
			re[(*j)++] = s[*i];
			s[(*i)++] = ' ';
		}
	}
}

int	write_io(char *re, char *s, int *in_q, int *j)
{
	int	i;

	i = 0;
	write_hed(re, s, &i, j);
	while (is_in(" \t\v\f\r\n", s[i]))
		i++;
	while (s[i]
		&& !((is_in("<>", s[i]) && !*in_q) || is_in(" \t\v\f\r\n", s[i])))
	{
		re[(*j)++] = s[i];
		if (s[i] == '"' || s[i] == '\'')
			isin_quo(s[i], in_q);
		s[i] = ' ';
		i++;
	}
	re[(*j)++] = ' ';
	return (i);
}

char	*rd_io(char *s)
{
	int		i;
	char	*re;
	int		in_quo;
	int		j;

	re = malloc(1024);
	if (!re)
		return (0);
	i = 0;
	j = 0;
	in_quo = 0;
	while (s[i])
	{
		if (is_io(&s[i]) && in_quo == 0)
			i += write_io(re, &s[i], &in_quo, &j);
		else if (s[i] == '"' || s[i] == '\'')
			isin_quo(s[i++], &in_quo);
		else
			i++;
	}
	re[j] = 0;
	re = sdupf(re);
	return (re);
}

char	**ld_io(char *s)
{
	char	*io;
	char	**re;

	io = rd_io(s);
	re = ft_split(io, " ");
	free(io);
	return (re);
}

void	ld_io3(t_sh *sh, char **cs)
{
	char	***re;
	int		i;

	i = -1;
	re = malloc((len2(cs) + 1) * sizeof(char **));
	while (cs[++i])
		re[i] = ld_io(cs[i]);
	re[i] = 0;
	sh->iof = re;
}
