/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:51:49 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/15 11:51:22 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

long long	ati(const char *str)
{
	long long	curr;
	int			i;
	long long	sign;

	i = 0;
	curr = 0;
	sign = 1;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		curr = 10 * curr + sign * (str[i] - 48);
		i++;
	}
	return (curr);
}

int	is_aphnum(char c)
{
	if (c == '_')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	all_sp(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] == ' ' || s[i] == '\t'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
