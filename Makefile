##
## Makefile
##
## Started on  Thu Mar  6 by Guillaume
## Update on Thu Mar  6 13:02 by Guillaume
##

NAME =	nibbler
DOBJ =	objects
DSRC =	sources

SRC =	sources/main.cpp \
		sources/nibbler.cpp

OBJ =	$(subst $(DSRC), $(DOBJ), $(SRC))
OBJ :=	$(OBJ:.cpp=.o)
CXXFLAG :=	-W -Wall -Wextra -ldl

CXX = clang++

all :	make
	@mkdir -p objects
	@echo -e "\033[32m"$(NAME) is up to date!  "\033[0m"

%.o :	%.cpp
	@mkdir -p objects
	@$(CXX) -o $(DOBJ)/$@ $(CXXFLAGS) $(LINK) -c $<

$(DOBJ)/%.o :	$(DSRC)/%.cpp
		@mkdir -p objects
		@$(CXX) $(CXXFLAGS) -o $@ $(LINK) -c $<
		@echo -e "\033[34mCompile :" $< $(CXXFLAGS) $(LINK) "\033[0m""\033[32m"[OK]"\033[0m"

$(DOBJ)/%.o :	%.cpp
		@mkdir -p objects
		@$(CXX) $(CXXFLAGS) -o $@ $(LINK) -c $<
		@echo -e "\033[34mCompile :" $< $(CXXFLAGS) $(LINK) "\033[0m""\033[32m"[OK]"\033[0m"

make :	$(OBJ)
	@mkdir -p objects
	@$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LINK)

clean :
	@rm -f $(OBJ)

fclean :	clean
		@rm -f $(NAME)

re :	fclean all
