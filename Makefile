##
## Makefile for makefile in /home/apollo/rendu/nibbler2/SDL
## 
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
## 
## Started on  Fri Mar 14 13:13:43 2014 ribeaud antonin
## Last update Fri Mar 14 13:18:35 2014 ribeaud antonin
##

NAME_EXE = nibbler
SRC_EXE = sources/main.cpp \
	sources/nibbler.cpp \

OBJ_EXE = $(SRC_EXE:.cpp=.o)

NAME_LIB = SDL.so
SRC_LIB = SDL/srcs/snake.cpp \

OBJ_LIB = $(SRC_LIB:.cpp=.o)

LDFLAGS += -ldl
CXXFLAGS += -fPIC

CXX = g++

all: $(NAME_LIB) $(NAME_EXE)

$(NAME_EXE): $(OBJ_EXE)
	$(CXX) -o $(NAME_EXE) $(OBJ_EXE) $(LDFLAGS)

$(NAME_LIB): $(OBJ_LIB)
	$(CXX) -shared -o $(NAME_LIB) $(OBJ_LIB)

clean:
	rm -f $(OBJ_LIB) $(OBJ_EXE)

fclean: clean
	rm -f $(NAME_EXE) $(NAME_LIB)

re: fclean all
