/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:04:51 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 01:38:05 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	cut_io(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (s[i] == '<' || s[i] == '>')
// 		i++;
// 	s[i] = 0;
// }

// char	**rld_io(char **s, int j)
// {
// 	int		i;
// 	char	**re;
// 	int		l;

// 	l = len2(s);
// 	re = malloc((l + 1) * sizeof(char *));
// 	if (!re)
// 		return (0);
// 	i = l + 1;
// 	while (--i > j + 1)
// 		re[i] = s[i - 1];
// 	re[i] = file_io(s[j]);
// 	cut_io(re[i - 1]);
// 	free(s);
// 	return (re);
// }

// char	**ld_io(char **s)
// {
// 	int		i;
// 	int		j;
// 	char	**re;

// 	j = 0;
// 	i = -1;
// 	re = malloc((len2(s) + 1) * sizeof(char *));
// 	while (s[++i])
// 	{
// 		if (is_io(s[i]) >= 'A' && is_io(s[i]) <= 'Z')
// 			re[j++] = sdup(s[i]);
// 		else if (is_io(s[i]) >= 'a' && is_io(s[i]) <= 'z')
// 			re[j++] = sjoin(s[i], s[i + 1]);
// 	}
// 	re[j] = 0;
// 	return (re);
// }

// void	ld_io3(t_sh *sh, char ***css)
// {
// 	char	***re;
// 	int		i;

// 	i = -1;
// 	re = malloc((len3(css) + 1) * sizeof(char **));
// 	while (css[++i])
// 		re[i] = ld_io(css[i]);
// 	re[i] = 0;
// 	sh->iof = re;
// }

// void	rld_io(char **cs)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (cs[i])
// 	{
// 		// fprint(2, "test\n");
// 		if (is_io(cs[i]) >= 'A' && is_io(cs[i]) <= 'Z')
// 			free(cs[i++]);
// 		else if (is_io(cs[i]) >= 'a' && is_io(cs[i]) <= 'z')
// 		{
// 			free(cs[i++]);
// 			if (cs[i])
// 				free(cs[i++]);
// 		}
// 		else
// 			cs[j++] = cs[i++];
// 	}
// 	cs[j] = 0;
// }

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
		// fprint(1, "test\n");
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
	// fprint(2, "%s|\n", s);
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
