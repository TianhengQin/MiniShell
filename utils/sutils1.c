/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutils1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:10:36 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 23:57:20 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	len2(char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

size_t	len3(char ***css)
{
	size_t	i;

	i = 0;
	while (css[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*trm_sp(char *s)
{
	int		i;
	char	*re;

	i = 0;
	while (s[i] && is_in(" \t\v\f\r\n", s[i]))
		i++;
	re = sdup(&s[i]);
	
	i = len(re) - 1;
	while (i >= 0 && is_in(" \t\v\f\r\n", re[i]))
		re[i--] = 0;
	free(s);
	// fprint(1, "%s\n",re);
	return (re);
}
