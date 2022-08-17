# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 22:55:01 by armaxima          #+#    #+#              #
#    Updated: 2022/08/17 17:21:48 by armaxima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_FT = ft_containers
NAME_STD = std_containers

SRC = main.cpp

DIR_FT = obj_ft
DIR_STD = obj_std

OBJ_FT = $(DIR_FT)/$(SRC:.cpp=.o)
OBJ_STD = $(DIR_STD)/$(SRC:.cpp=.o)

INC = vector/vector.hpp \
	vector/vector_iterator.hpp \
	vector/random_iterator.hpp \
	utils/utils.hpp \
	stack/stack.hpp \
	map/map.hpp \
	map/pair.hpp \
	map/TreeNode.hpp \
	map/map_iterator.hpp

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
	rm -rf $(OBJ_FT) $(OBJ_STD)

fclean: clean
	rm -rf $(NAME_FT) $(NAME_STD)

re: fclean all

.PHONY: all clean fclean re test
