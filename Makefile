# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 00:47:44 by abkasmi           #+#    #+#              #
#    Updated: 2022/05/19 04:02:22 by abkasmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c \
		srcs/thread_init.c \
		srcs/init_struct.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/routine.c

OBJS = $(SRCS:.c=.o)

NAME = philo

RM = rm -rf

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

%.o:	%.c
			gcc ${FLAGS} -c $< -o ${@:.c=.o}
			
$(NAME) : $(OBJS)
			gcc $(OBJS) -o $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
			$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re