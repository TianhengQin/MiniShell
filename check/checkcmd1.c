/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:26:52 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 09:28:58 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ck_start(char *cmd)
{
	if (cmd[0] == '|')
	{
		fprint(2, "minishell: syntax error near ");
		fprint(2, "unexpected token `|'\n");
		return (1);
	}
	return (0);
}
