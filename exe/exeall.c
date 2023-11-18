/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:37 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/18 10:38:37 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exe_all(t_sh *sh, char ***css)
{
	if (len3(css) == 1)
		exe_cmd(sh, css[0]);
	else
		exe_pip(sh, css);
	if (sh->exit_c == 130)
		write(1, "\n", 1);
	else if (sh->exit_c == 131)
		write(2, "Quit: 3\n", 8);
}
