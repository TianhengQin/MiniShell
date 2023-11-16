/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:41:56 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 05:52:29 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	redir_o(t_sh *sh, char *io)
{
	int		out;

	if (io[0] == '1')
	{
		out = open(&io[io[0] - 47], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else
	{
		out = open(&io[io[0] - 47], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	}
	if (out == -1)
	{
		perror("minishell");
		sh->exe = 0;
		sh->exit_c = 1;
		return ;
	}
	dup2(out, 1);
	close(out);
	sh->exit_c = 0;
}

void	redir_i(t_sh *sh, char *io)
{
	int		in;

	in = open(&io[io[0] - 47], O_RDONLY, S_IRWXU);
	if (in == -1)
	{
		perror("minishell");
		sh->exe = 0;
		sh->exit_c = 1;
		return ;
	}
	dup2(in, 0);
	close(in);
	sh->exit_c = 0;
}

void	redir(t_sh *sh, char **io)
{
	int	i;

	sh->stdi = dup(0);
	sh->stdo = dup(0);
	i = -1;
	while (io[++i])
	{
		if (io[i][1] == '>')
			redir_o(sh, io[i]);
		else if (io[i][0] == '1')
			redir_i(sh, io[i]);
		else
		{
			hir_doc(sh, &io[i][io[i][0] - 47], 'l');
		}
	}
}
