DIR		:=	.

HDR		:=	Prompt.hpp Error.hpp

SRC		:=	Prompt.cpp Error.cpp main_predict.cpp

HDR_T	:=	Error.hpp

SRC_T	:=	Error.cpp main_train.cpp

HDR		:=	$(HDR:%.hpp=$(DIR)/hdr/%.hpp)

HDR_T	:=	$(HDR_T:%.hpp=$(DIR)/hdr/%.hpp)

SRC		:=	$(SRC:%.cpp=$(DIR)/src/%.cpp)

SRC_T	:=	$(SRC_T:%.cpp=$(DIR)/src/%.cpp)

OBJ		:=	$(SRC:$(DIR)/src/%.cpp=$(DIR)/obj/%.o)

OBJ_T	:=	$(SRC_T:$(DIR)/src/%.cpp=$(DIR)/obj/%.o)

CFLAGS	+=	-Wall -Wextra -Werror -Wshadow -g -I$(DIR)/hdr

CC		:=	c++

NAME	:=	Predict

NAME_T	:=	Training

all		:	$(NAME) $(NAME_T)

$(NAME)				:	$(OBJ)
						$(CC) $(CFLAGS) $^ -o $@

$(NAME_T)			:	$(OBJ_T)
						$(CC) $(CFLAGS) $^ -o $@

$(DIR)/obj/%.o		:	./src/%.cpp $(HDR) | ./obj
						$(CC) $(CFLAGS) -c $< -o $@

./obj				:
						mkdir obj

clean				:
						rm -rf ./obj

fclean				:	clean
						rm -rf $(NAME) $(NAME_T)

re					:	fclean all

.PHONY				:	all clean fclean re
