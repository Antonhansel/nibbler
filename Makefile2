##
## Makefile<2> for Makefile in /home/apollo/rendu/OPENGL_TUTO/test1
## 
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
## 
## Started on  Mon Mar 10 15:07:46 2014 ribeaud antonin
## Last update Thu Mar 13 17:43:55 2014 ribeaud antonin
##

NAME		=	snake

SRCS		=	srcs/snake.cpp \
			srcs/main.cpp \

OBJS		=	$(SRCS:.cpp=.o)

CFLAGS		+=	-lSDL -lSDL_mixer -lSDL_image -fPIC

LDFLAGS		=	-shared

CC		=	g++ -shared

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean		:
			rm -f $(OBJS)

fclean		:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
