/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 02:30:21 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/17 02:06:48 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	write_quo(char c, char *re, int *j, int in_quo)
{
	if (in_quo == 0 || c == -1)
		return ;
	if (in_quo == 1 && c == '"')
		re[(*j)++] = c;
	else if (in_quo == 2 && c == '\'')
		re[(*j)++] = c;
	else if (in_quo < 0)
		re[(*j)++] = c;
}

char	*dequo(char *re)
{
	int		i;
	int		in_quo;
	int		j;

	j = 0;
	i = -1;
	in_quo = 0;
	while (re[++i])
	{
		if (re[i] == '\'' || re[i] == '"')
		{
			write_quo(re[i], re, &j, in_quo);
			isin_quo(re[i], &in_quo);
		}
		else
			re[j++] = load_quo(re[i]);
	}
	re[j] = 0;
	return (re);
}

char	**dequo2(char **re)
{
	int	i;

	i = -1;
	while (re[++i])
		re[i] = dequo(re[i]);
	return (re);
}

char	***dequo3(char ***re)
{
	int	i;

	i = -1;
	while (re[++i])
		re[i] = dequo2(re[i]);
	return (re);
}
