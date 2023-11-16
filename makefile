BUIN	= cd echo env exit export export1 pwd unset

EXE		= exeall exeone exepip

RDIR	= io resetio heredoc

PIPE	= setpip

RLOD	= dequo quo loadio

SIG		= signal signal1

SPLT	= splitcmd eachcmd

UTIL	= free ft_printf ft_split strjoin strjoin2 sutils sutils1 utils

INIT	= set

CHCK	= checkcmd checkcmd1

SRCS	= $(addsuffix .c, $(addprefix buildin/, $(BUIN))) \
		$(addsuffix .c, $(addprefix init/, $(INIT))) \
		$(addsuffix .c, $(addprefix redir/, $(RDIR))) \
		$(addsuffix .c, $(addprefix reloadcmd/, $(RLOD))) \
		$(addsuffix .c, $(addprefix signal/, $(SIG))) \
		$(addsuffix .c, $(addprefix splitcmd/, $(SPLT))) \
		$(addsuffix .c, $(addprefix utils/, $(UTIL))) \
		$(addsuffix .c, $(addprefix check/, $(CHCK))) \
		$(addsuffix .c, $(addprefix exe/, $(EXE))) \
		$(addsuffix .c, $(addprefix pipe/, $(PIPE))) \
		main.c

OBJS	= $(SRCS:.c=.o)
INCL	= ./
NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -lreadline
CC		= cc


all:$(NAME)

$(NAME):$(SRCS)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -I $(INCL)

re:fclean all

fclean:clean
		rm -f $(NAME)

clean:
		rm -f $(OBJS)

.PHONY: clean fclean all re