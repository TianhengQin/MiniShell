/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:10:30 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/16 02:42:54 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:31:59 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/10 12:29:53 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

# define HERE_DOC_NAME ".here_doc_a72>7!e;wL=rouN]>uO46#bI1av85:ZX<tkCl8CPR.txt"

long long	g_s;

typedef struct s_sh
{
	int			runing;
	char		*pwd;
	char		*odpwd;
	char		**env;
	char		*home;
	char		*user;
	char		**evpth;
	int			child;
	int			exe;
	int			*pip;
	char		***iof;
	int			stdi;
	int			stdo;
	long long	exit_c;
	int			pidf;
}	t_sh;

//utils
int			fprint(int fd, const char *s, ...);
char		*sjoin(char const *s1, char const *s2);
char		*sjoinf1(char const *s1, char const *s2);
char		*sjoinf2(char const *s1, char const *s2);
char		*sjoin2(int size, char **strs, char *sep);
size_t		len(const char *str);
size_t		len2(char **str);
size_t		len3(char ***css);
char		**ft_split(char const *s, char *c);
char		*sdup(const char *src);
char		*sdupf(const char *src);
int			sncmp(const char *s1, const char *s2, int n);
long long	ati(const char *str);
int			is_aphnum(char c);
int			is_apha(char c);
int			all_sp(char *s);
char		is_in(char *s, char c);
//init
void		set_env(t_sh *shell);
void		set_env_r(t_sh *shell);
void		set_envpth(t_sh *sh);
void		set_signal_b(void);
void		set_signal_a(void);
void		rm_signal(void);
int			find(char **str, char *s);
//prase quo
char		*dequo(char *re);
char		*quo(t_sh *sh, char *c);
char		**quo2(t_sh *sh, char **cs);
char		***quo3(t_sh *sh, char ***css);
char		***dequo3(char ***re);
void		isin_quo(char c, int *in_quo);
void		write_quo(char c, char *re, int *j, int in_quo);
int			write_dolor(char *c, t_sh *sh, char *re, int *j);
//prase io
char		is_io(char *s);
void		ld_io3(t_sh *sh, char **cs);
//split cmd
char		***all_cmd(t_sh *sh, char *s);
char		***splt3(char ***css);
//vaild cmd
int			check(char *s, char ***css, t_sh *sh);
//exe
void		exe_cmd(t_sh *sh, char **cs);
void		exe_all(t_sh *sh, char ***css);
void		exe_pip(t_sh *sh, char ***css);
char		*get_pth(char *pwd, char **evpth, char *cs);
//buildin
void		run_echo(t_sh *sh, char **cs);
void		run_pwd(t_sh *sh, char **cs);
void		run_cd(t_sh *sh, char **cs);
void		run_env(t_sh *sh, char **cs);
void		env_append(t_sh *sh, char *cs);
void		env_delete(t_sh *sh, int i);
void		run_export(t_sh *sh, char **cs);
char		*prase_exp(char *cs);
int			valid_exp(char *s);
void		run_unset(t_sh *sh, char **cs);
void		run_exit(t_sh *sh, char **cs);
//redir
void		redir(t_sh *sh, char **io);
void		hir_doc(t_sh *sh, char *lmt, char m);
void		crt_hirdoc(t_sh *sh);
void		send_line(char *cs, int fd);
void		reset_io(t_sh *sh);
//pipe
void		set_pip(t_sh *sh);
void		close_pip(t_sh *sh, int j);
//free
void		free2(char **cs);
void		free3(char ***css);
void		free_sh(t_sh *sh);
void		free_cmd(char *cmd, char ***css, t_sh *sh);
void		free_fail(t_sh *sh, char **cs);
//debug
void		prnt(char ***css);

#endif