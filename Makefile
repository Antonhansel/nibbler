##
## Makefile for makefile in /home/apollo/rendu/nibbler2/SDL
## 
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
## 
## Started on  Fri Mar 14 13:13:43 2014 ribeaud antonin
## Last update Mon Mar 17 21:01:35 2014 ribeaud antonin
##

NAME_EXE        = nibbler
SRC_EXE         = sources/main.cpp \
		sources/nibbler.cpp \

OBJ_EXE         = $(SRC_EXE:.cpp=.o)

NAME_LIB        = lib_nibbler_SDL.so
SRC_LIB         = SDL/snake.cpp
SDL_FLAG        = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OBJ_LIB         = $(SRC_LIB:.cpp=.o)

NAME_NC        = lib_nibbler_ncurses.so
SRC_NC         = ncurses/snake.cpp
NC_FLAG        = -lncurses
OBJ_NC         = $(SRC_NC:.cpp=.o)

LDFLAGS         += -ldl
CXXFLAGS        += -fPIC #-Wall -Werror -Werror

CXX             = g++

all:		$(NAME_LIB) $(NAME_NC) $(NAME_EXE)

$(NAME_EXE):	$(OBJ_EXE)
		$(CXX) -o $(NAME_EXE) $(OBJ_EXE) $(LDFLAGS)

$(NAME_LIB):	$(OBJ_LIB)
		$(CXX) -shared -o $(NAME_LIB) $(OBJ_LIB) $(SDL_FLAG)

$(NAME_NC):	$(OBJ_NC)
		$(CXX) -shared -o $(NAME_NC) $(OBJ_NC) $(NC_FLAG)

clean:
		rm -f $(OBJ_LIB) $(OBJ_EXE) $(OBJ_NC)

fclean:		clean
		rm -f $(NAME_EXE) $(NAME_LIB) $(NAME_NC)

re:		fclean all
