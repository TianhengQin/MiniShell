/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:40:38 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/11 01:11:56 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*sdup(const char *src)
{
	char	*dup;
	int		i;

	i = 0;
	while (src[i])
	{
		i++;
	}
	dup = (char *)malloc(i + 1);
	if (!dup)
		return (0);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = src[i];
	return (dup);
}

char	*sdupf(const char *src)
{
	char	*dup;
	int		i;

	i = 0;
	while (src[i])
	{
		i++;
	}
	dup = (char *)malloc(i + 1);
	if (!dup)
		return (0);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = src[i];
	free((char *)src);
	return (dup);
}

int	sncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (i < n)
	{
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
