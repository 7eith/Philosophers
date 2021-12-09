# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 15:56:49 by amonteli          #+#    #+#              #
#    Updated: 2021/12/09 17:01:30 by amonteli         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


NAME			=		philo

INC_DIR			=		includes

HEADERS			=		includes/philosophers.h

CC				=		gcc

CFLAGS 			= 		-Wall -Wextra -Werror

SRCS			=		\
						main.c utilities.c tasks.c

OBJS			= 		$(addprefix srcs/, $(SRCS:.c=.o))

all				: 		$(NAME)

$(NAME)		: $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -I $(HEADERS) -o $(NAME)

%.o: %.c $(HEADERS)
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
		@echo "\033[34m[Philosophers] Compiled $<\033[0m"

bonus		:		$(NAME)

clean		:
		@/bin/rm -f $(OBJS)
		@echo "\033[90m[\033[91mPhilosophers\033[90m]\033[31m Deleted *.o\033[0m"

fclean		:		clean
		@/bin/rm -f $(NAME)
		@echo "\033[90m[\033[91mPhilosophers\033[90m]\033[31m Deleted $(NAME)\033[0m"

norme		:
		@norminette srcs/
		@norminette includes/

re			:		fclean all
