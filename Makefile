# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 22:55:01 by armaxima          #+#    #+#              #
#    Updated: 2022/08/08 17:27:42 by armaxima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_FT = ft_containers
NAME_STD = std_containers

SRC = main.cpp

DIR_FT = obj_ft
DIR_STD = obj_std

OBJ_FT = $(DIR_FT)/$(SRC:.cpp=.o)
OBJ_STD = $(DIR_STD)/$(SRC:.cpp=.o)

INC = vector.hpp \
	vector_iterator.hpp \
	random_iterator.hpp \
	utils.hpp

CPP = c++

FLAGS = -Wall -Wextra -Werror -I. -std=c++98

$(DIR_STD)/%.o : %.cpp
	mkdir -p $(DIR_STD)
	$(CPP) $(FLAGS) -D NM=std -c $< -o $@

$(DIR_FT)/%.o : %.cpp
	mkdir -p $(DIR_FT)
	$(CPP) $(FLAGS) -c $< -o $@

all: $(NAME_STD) $(NAME_FT)

$(NAME_STD): $(OBJ_STD) $(INC) $(SRC)
	$(CPP) $(FLAGS) -D NM=std $(OBJ_STD) -o $(NAME_STD)

$(NAME_FT): $(OBJ_FT) $(INC) $(SRC)
	$(CPP) $(FLAGS) $(OBJ_FT) -o $(NAME_FT)

clean:
	rm -f $(OBJ_FT) $(OBJ_STD)

fclean: clean
	rm -rf $(NAME_FT) $(NAME_STD)

re: fclean all

.PHONY: all clean fclean re test
