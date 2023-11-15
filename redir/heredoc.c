/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:24:35 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/15 19:46:50 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	send_line(char *cs, int fd)
{
	char	*line;
	char	*endl;

	while (1)
	{
		line = readline("heredoc> ");
		endl = sjoin(line, "\n");
		if (sncmp(line, cs, 2147483647) == 0)
		{
			free(endl);
			free(line);
			return ;
		}
		write(fd, endl, len(endl));
		free(endl);
		free(line);
	}
}

void	hir_doc(t_sh *sh, char *lmt, char m)
{
	int	hd;

	if (m == 'c')
	{
		hd = open(HERE_DOC_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
		if (hd < 0)
			return ;
		send_line(lmt, hd);
		close(hd);
	}
	else if (m == 'l')
	{
		hd = open(HERE_DOC_NAME, O_RDONLY);
		if (hd == -1)
		{
			unlink(HERE_DOC_NAME);
			perror("minishell");
			sh->exe = 0;
			sh->exit_c = 1;
			return ;
		}
		dup2(hd, 0);
		close(hd);
	}
}

void	crt_hirdoc(t_sh *sh)
{
	int	i;
	int	j;

	i = -1;
	while (sh->iof[++i])
	{
		j = -1;
		while (sh->iof[i][++j])
		{
			// fprint(2, "%s\n", sh->iof[i][j]);
			if (sh->iof[i][j][0] == '2' && sh->iof[i][j][1] == '<')
			{
				// fprint(2, "oneheredoc\n");
				hir_doc(sh, &sh->iof[i][j][sh->iof[i][j][0] - 47], 'c');
			}
		}
	}
}
