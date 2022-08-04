# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 22:55:01 by armaxima          #+#    #+#              #
#    Updated: 2022/08/01 20:17:25 by armaxima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

INC = vector.hpp \
	vector_iterator.hpp \
	utils.hpp

CPP = c++

FLAGS = -Wall -Wextra -Werror -I. -std=c++98

%.o : %.c
	$(CPP) $(FLAGS) -c $< -o $@ -I $(INC)

all: $(NAME)

$(NAME): $(OBJ) $(INC) $(SRC)
	$(CPP) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
