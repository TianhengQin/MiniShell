/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:31:11 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/14 09:10:39 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	tot_l(int size, char **strs, char *sep)
{
	int	tot;
	int	lp;
	int	i;

	i = 0;
	lp = len(sep);
	tot = 0;
	while (i < size)
	{
		tot += len(strs[i]);
		i++;
	}
	return (tot + (size - 1) * lp);
}

void	str_cat(char *re, char **strs, int *cur, int i)
{
	int	j;

	j = 0;
	while (strs[i][j])
	{
		re[*cur] = strs[i][j];
		j++;
		*cur = *cur + 1;
	}
}

char	*sjoin2(int size, char **strs, char *sep)
{
	char	*re;
	int		i;
	int		j;
	int		curr;

	if (size == 0)
		return (sdup(""));
	re = (char *)malloc(tot_l(size, strs, sep) + 1);
	if (!re)
		return (sdup(""));
	i = 0;
	curr = 0;
	while (i < size)
	{
		str_cat(re, strs, &curr, i);
		j = 0;
		while (sep[j] && i < size - 1)
			re[curr++] = sep[j++];
		i++;
	}
	re[curr] = 0;
	return (re);
}
