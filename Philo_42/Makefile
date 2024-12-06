# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 17:44:12 by lboumahd          #+#    #+#              #
#    Updated: 2024/12/06 12:45:11 by lboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = *.c

MANPATH = $(addprefix ./src/, $(SRC))

FLAGS = -Wall -Wextra -Werror -g -pthread

HEADER = ./src/philo.h

# SANITIZER = -fsanitize=thread

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH) $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all