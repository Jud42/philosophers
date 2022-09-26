# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 18:02:56 by rmamison          #+#    #+#              #
#    Updated: 2022/09/19 14:04:28 by rmamison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	main.c \
	atoi.c	\

SRCS = $(addprefix srcs/, $(SRC))
DIR_S = srcs

INCLUDE = -I ./includes

FLAGS = -Wall -Wextra -Werror -g3 -o0 -fsanitize=address
CC = gcc

RM = rm -rf

DIR = file_object
OB = $(addprefix $(DIR)/, $(SRCS:%.c=%.o))
CLONE = file_object \
	file_object/srcs \

$(DIR)/%.o : %.c
	@mkdir -p $(CLONE)
	@$(CC) $(INCLUDE) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OB)
	@echo "Compiling philo..."
	@$(CC) $(FLAGS) $(OB) -o $@
	@echo "Compilation [philo] is done!"

clean :
	@echo "Remove all file_object..."
	@$(RM) $(DIR)
	@echo "file_object removed!"

fclean : clean
	@echo "Remove all file_object & file_binary..."
	@$(RM) $(NAME)
	@echo "object and binary_file removed!"

re : fclean $(NAME)
.PHONY: all clean fclean re