/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:01:15 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/15 12:09:05 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*cut_io(char *s)
{
	int	i;

	i = 1;
	if (i <= s[0] - 48)
		i++;
	s[i + 1] = 0;
	return (s + 1);
}

int	ck_endl(char *s)
{
	int	i;

	i = len(s) - 1;
	while (s[i] == ' ' && i > 0)
		i--;
	if (s[i] == '|')
		return (1);
	return (0);
}

int	ck_io(char ***iof, int j, int ck)
{
	int	i;

	i = -1;
	while (iof[j][++i])
	{
		if (is_io(iof[j][i] + 1) >= 'a' && is_io(iof[j][i] + 1) <= 'z')
		{
			fprint(2, "minishell: syntax error near unexpected");
			if (iof[j][i + 1])
				fprint(2, " token `%s'\n", cut_io(iof[j][i + 1]));
			else if (iof[j + 1] || ck)
			{
				fprint(2, "token `|'\n");
			}
			else
				fprint(2, "token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	ck_mid(char ***css, char ***iof, int ck)
{
	int	i;

	i = -1;
	while (css[++i])
	{
		if (ck_io(iof, i, ck))
		{
			return (1);
		}
		if (css[i][0] == 0 && iof[i][0] == 0)
		{
			fprint(2, "minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	return (0);
}

int	check(char *s, char ***css, t_sh *sh)
{
	int	ck;

	if (!css[0] || !css[0][0])
		return (1);
	if (!css[0][0][0])
	{
		fprint(2, "minishell: : command not found\n");
		sh->exit_c = 127;
		return (1);
	}
	ck = ck_endl(s);
	if (ck_mid(css, sh->iof, ck))
	{
		sh->exit_c = 258;
		return (1);
	}
	if (ck)
	{
		fprint(2, "minishell: syntax error near ");
		fprint(2, "unexpected token `newline'\n");
		sh->exit_c = 258;
		return (1);
	}
	return (0);
}
