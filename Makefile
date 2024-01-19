#*******************************  VARIABLES  **********************************#

RED			=		\033[1;31m
GREEN		=		\033[1;32m
YELLOW		=		\033[1;33m
BLUE		=		\033[1;34m
CYAN		=		\033[1;36m
DEFAULT		=		\033[0m
SUPPR		=		\r\033[2K
NAME		=		IRC

define HEADER
"\e[2J\e[H\033[1;36m
	  _____ _____   _____
	 |_   _|  __ \ / ____|
	   | | | |__) | |
	   | | |  _  /| |
	  _| |_| | \ \| |____
	 |_____|_|  \_\\\_____|
\033[0m
endef
export HEADER

MUTE		:=		1

# --------------- FILES --------------- #

LIST_SRC		=	main.cpp	\
					parsingUtils.cpp	\
					server.cpp			\
					client.cpp			\
					clientCommand.cpp	\
					serverCommand.cpp	\
					channel.cpp

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

all:	header $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		$(OBJ)
ifeq ($(MUTE),1)
	@$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ)
	@echo -n "${SUPPR} ${GREEN}	${NAME} : 🆗${DEFAULT}\n"
else
	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ)
endif

# ---------- COMPILED RULES ----------- #

-include $(DEP)

$(DIR_BUILD)%.o: %.cpp
	@mkdir -p $(shell dirname $@)
ifeq ($(MUTE),1)
	@$(CXX) $(CPPFLAGS) $(DEP_FLAGS) -I $(DIR_INCLUDE) -c $< -o $@
	@echo -n "${YELLOW}${SUPPR}	⌛ Creating IRC objects : $@"
else
	$(CXX) $(CPPFLAGS) $(DEP_FLAGS) -I $(DIR_INCLUDE) -c $< -o $@
endif

clean:
	$(RM) $(DIR_BUILD)

fclean:	clean
	$(RM) $(NAME)

header:
	@echo "$$HEADER"

re:		fclean
	@$(MAKE) all --no-print-directory

.PHONY:	re clean fclean all header
