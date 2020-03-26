# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparekh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 12:43:24 by vparekh           #+#    #+#              #
#*   Updated: 2020/03/02 17:54:08 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

BINARY = philo_three

COMP = gcc -Wall -Wextra -fsanitize=address -g3
# COMP = gcc -Wall -Wextra -g3
INCLUDES = -Iincludes
SRC := $(wildcard srcs/*.c)
OBJ := $(patsubst srcs/%.c, obj/%.o, $(SRC))
GREEN='\033[01;32m'
RESET='\033[00m'

all: $(BINARY)

$(BINARY): $(OBJ)
	@echo  "$(GREEN).................Making philo_one................ $(RESET)"
	$(COMP) $(INCLUDES) $(OBJ) -o $(BINARY) -l pthread

obj/%.o: srcs/%.c
	mkdir -p obj
	$(COMP) -Iincludes -c $< -o $@

norme:
	norminette srcs/*
	norminette includes/*

clean: 
		rm -rf obj/*

fclean: clean
	rm -rf $(BINARY) *.dSYM

re: fclean all

