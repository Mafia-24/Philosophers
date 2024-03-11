# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 21:13:39 by ymafaman          #+#    #+#              #
#    Updated: 2024/03/11 01:43:05 by ymafaman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Wextra -Werror -fsanitize=address

CFILES = destroying/destroying.c parsing/array_to_num_bonus.c parsing/parsing_1_bonus.c parsing/str_functions_bonus.c \
		   simulation/initializer.c simulation/monitor.c simulation/simulation_doer_bonus.c simulation/simulation_starter_bonus.c \
		   simulation/time.c main_bonus.c

OFILES = $(CFILES:.c=.o)

EXEC = philo_bonus

all : $(EXEC)

$(EXEC) : $(OFILES)
		$(CC) $(FLAGS) $(OFILES) -o $(EXEC)

%.o : %.c philosophers_bonus.h
		$(CC) $(FLAGS) $< -c -o $@

clean : 
		rm -f $(OFILES)

fclean : clean
		rm -f $(EXEC)

re : fclean all

.PHONY : clean