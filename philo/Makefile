# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 21:13:39 by ymafaman          #+#    #+#              #
#    Updated: 2024/03/09 21:52:53 by ymafaman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Wextra -Werror

CFILES = destroying/destroyer.c parsing/array_to_num.c parsing/parsing_1.c parsing/str_functions.c \
		 simulation/initializer.c simulation/monitoring.c simulation/notifying.c simulation/simulation_doer.c \
		 simulation/simulation_starter.c simulation/timer.c main.c

OFILES = $(CFILES:.c=.o)

EXEC = philo

all : $(EXEC)

$(EXEC) : $(OFILES)
		$(CC) $(FLAGS) $(OFILES) -o $(EXEC)

%.o : %.c philosophers.h 
		$(CC) $(FLAGS) $< -c -o $@

clean : 
		rm -f $(OFILES)

fclean : clean
		rm -f $(EXEC)

re : fclean all

.PHONY : clean