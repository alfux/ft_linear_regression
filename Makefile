DIR		:=	.

HDR		:=	Prompt.hpp Error.hpp

SRC		:=	Prompt.cpp Error.cpp main.cpp

HDR		:=	$(HDR:%.hpp=$(DIR)/hdr/%.hpp)

SRC		:=	$(SRC:%.cpp=$(DIR)/src/%.cpp)

OBJ		:=	$(SRC:$(DIR)/src/%.cpp=$(DIR)/obj/%.o)

CFLAGS	+=	-Wall -Wextra -Werror -Wshadow -g -I$(DIR)/hdr

CC		:=	c++

NAME	:=	Predict

TNAME	:=	Training

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $^ -o $@

$(DIR)/obj/%.o		:	./src/%.cpp ./obj $(HDR)
					$(CC) $(CFLAGS) -c $< -o $@

./obj	:
			mkdir obj

clean	:
			rm -rf ./obj

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
