/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:09:05 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/18 10:46:21 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	is_io(char *s)
{
	if (s[0] == '<' && s[1] == 0)
		return ('i');
	if (s[0] == '>' && s[1] == 0)
		return ('o');
	if (s[0] == '<' && s[1] == '<' && s[2] == 0)
		return ('d');
	if (s[0] == '>' && s[1] == '>' && s[2] == 0)
		return ('a');
	if (s[0] == '<' && s[1] == '<')
		return ('D');
	if (s[0] == '>' && s[1] == '>')
		return ('A');
	if (s[0] == '<')
		return ('I');
	if (s[0] == '>')
		return ('O');
	return (0);
}

// char	**splt_io(char **s)
// {
// 	int		i;
// 	char	**re;
// 	char	rld;

// 	rld = 1;
// 	while (rld)
// 	{
// 		rld = 0;
// 		i = 0;
// 		while (s[i])
// 		{
// 			if (is_io(s[i]) >= 'A')
// 			{
// 				rld = 1;
// 				re = rld_io(s, i);
// 			}
// 			i++;
// 		}
// 	}
// 	return (re);
// }

char	***splt_cmd(t_sh *sh, char *s)
{
	char	**cs;
	char	***css;
	int		i;

	cs = ft_split(s, "|");
	if (!cs)
		return (0);
	i = len2(cs);
	css = malloc((i + 1) * sizeof(char **));
	if (!css)
	{
		free2(cs);
		return (0);
	}
	ld_io3(sh, cs);
	css[i] = 0;
	while (--i >= 0)
		css[i] = ft_split(cs[i], " \t\v\f\r\n");
	free2(cs);
	return (css);
}

char	**quo2(t_sh *sh, char **cs)
{
	int	i;

	i = 0;
	while (cs[i])
	{
		cs[i] = quo(sh, cs[i]);
		i++;
	}
	return (cs);
}

char	***quo3(t_sh *sh, char ***css)
{
	int	i;

	i = 0;
	while (css[i])
	{
		css[i] = quo2(sh, css[i]);
		i++;
	}
	return (css);
}

// void	prnt(char ***css)
// {
// 	int i = 0;
// 	int j = 0;
// 	while (css[i])
// 	{
// 		j = 0;
// 		while (css[i][j])
// 		{
// 			printf("[%s]", css[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

char	***all_cmd(t_sh *sh, char *s)
{
	char	***re;

	re = splt_cmd(sh, s);
	re = quo3(sh, re);
	sh->iof = quo3(sh, sh->iof);
	re = splt3(re);
	re = dequo3(re);
	sh->iof = dequo3(sh->iof);
	return (re);
}
