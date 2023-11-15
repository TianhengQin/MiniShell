/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resetio.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 05:19:52 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/15 05:38:56 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	reset_io(t_sh *sh)
{
	if (sh->stdi != -1)
		dup2(sh->stdi, 0);
	if (sh->stdi != -1)
		dup2(sh->stdo, 1);
	sh->stdi = -1;
	sh->stdo = -1;
}
