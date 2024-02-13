DIR		:=	.

HDR		:=	Error.hpp Prompt.hpp
HDR		:=	$(HDR:%.hpp=$(DIR)/hdr/%.hpp)

SRC		:=	Error.cpp Prompt.cpp main_predict.cpp
SRC		:=	$(SRC:%.cpp=$(DIR)/src/%.cpp)

HDR_T	:=	Error.hpp Plot.hpp
HDR_T	:=	$(HDR_T:%.hpp=$(DIR)/hdr/%.hpp)

SRC_T	:=	Error.cpp Plot.cpp main_train.cpp
SRC_T	:=	$(SRC_T:%.cpp=$(DIR)/src/%.cpp)

HDR_A	:=	Error.hpp Accuracy.hpp
HDR_A	:=	$(HDR_P:%.hpp=$(DIR)/hdr/%.hpp)

SRC_A	:=	Error.cpp Accuracy.cpp main_accuracy.cpp
SRC_A	:=	$(SRC_A:%.cpp=$(DIR)/src/%.cpp)

OBJ		:=	$(SRC:$(DIR)/src/%.cpp=$(DIR)/obj/%.o)
OBJ_T	:=	$(SRC_T:$(DIR)/src/%.cpp=$(DIR)/obj/%.o)
OBJ_A	:=	$(SRC_A:$(DIR)/src/%.cpp=$(DIR)/obj/%.o)

SDLL	:=	$(shell sdl2-config --libs)
SDLI	:=	$(shell sdl2-config --cflags)

CFLAGS	+=	-Wall -Wextra -Werror -Wshadow -g -I$(DIR)/hdr -DGL_SILENCE_DEPRECATION
CC		:=	c++

NAME	:=	Predict
NAME_T	:=	Training
NAME_A	:=	Accuracy

all		:	$(NAME) $(NAME_T) $(NAME_A)

$(NAME)				:	$(OBJ)
						$(CC) $(CFLAGS) $(SDLL) $^ -o $@

$(NAME_T)			:	$(OBJ_T)
						$(CC) $(CFLAGS) $(SDLL) $^ -o $@

$(NAME_A)			:	$(OBJ_A)
						$(CC) $(CFLAGS) $(SDLL) $^ -o $@

$(DIR)/obj/%.o		:	./src/%.cpp $(HDR) $(HDR_T) $(HDR_A) | ./obj
						$(CC) $(CFLAGS) $(SDLI) -c $< -o $@

./obj				:
						mkdir obj

clean				:
						rm -rf ./obj

fclean				:	clean
						rm -rf $(NAME) $(NAME_T) $(NAME_A)
						rm -rf .data

re					:	fclean all

.PHONY				:	all clean fclean re
