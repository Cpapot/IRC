#*******************************  VARIABLES  **********************************#

RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
DEFAULT		=	\033[0m
SUPPR		=	\r\033[2K
NAME		=	IRC

# --------------- FILES --------------- #

LIST_SRC		=	main.cpp	\
					parsingUtils.cpp	\
					server.cpp			\
					client.cpp			\
					clientCommand.cpp	\
					serverCommand.cpp

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=		.build/
DIR_SRC			=		srcs/
DIR_INCLUDE		=		inc/

# ------------- SHORTCUTS ------------- #

OBJ                =    $(patsubst %.cpp, $(DIR_BUILD)%.o, $(SRC))
DEP                =    $(patsubst %.cpp, $(DIR_BUILD)%.d, $(SRC))
SRC                =    $(addprefix $(DIR_SRC),$(LIST_SRC))

# ------------ COMPILATION ------------ #

CPPFLAGS        =    -Wall -Wextra -Werror -std=c++98 -g

DEP_FLAGS        =    -MMD -MP

CXX              =    c++

# -------------  COMMANDS ------------- #

RM                =    rm -rf
MKDIR            =    mkdir -p

#***********************************  RULES  **********************************#

.PHONY: all
all:            $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		$(OBJ)
			$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ)

# ---------- COMPILED RULES ----------- #

-include $(DEP)

$(DIR_BUILD)%.o: %.cpp
			mkdir -p $(shell dirname $@)
			$(CXX) $(CPPFLAGS) $(DEP_FLAGS) -I $(DIR_INCLUDE) -c $< -o $@

.PHONY:	clean
clean:
			$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
			$(RM) $(NAME)

.PHONY:	re
re:		fclean
			$(MAKE) all
