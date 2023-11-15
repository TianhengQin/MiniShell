/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eachcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:57:04 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/14 05:35:52 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**splt2(char **cs)
{
	char	**re;
	char	*tot;

	tot = sjoin2(len2(cs), cs, " ");
	re = ft_split(tot, ' ');
	free(tot);
	free2(cs);
	return (re);
}

char	***splt3(char ***css)
{
	int	i;

	i = 0;
	while (css[i])
	{
		css[i] = splt2(css[i]);
		i++;
	}
	return (css);
}

/*
split with |
reload io
split with ' '
quo
split with ' '
dequo
*/