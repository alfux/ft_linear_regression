SRC		:=	main.cpp

OBJ		:=	$(SRC:%.cpp=%.o)

HDR		:=	$(shell pwd)

CFLAGS	+=	-Wall -Wextra -Werror -Wshadow -g -I$(HDR)

CC		:=	c++

NAME	:=	ft_linear_regression

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $^ -o $@

%.o		:	%.cpp $(HDR)
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			rm -rf $(OBJ)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
