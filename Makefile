#*******************************  VARIABLES  **********************************#

RED			=		\033[1;31m
GREEN		=		\033[1;32m
YELLOW		=		\033[1;33m
BLUE		=		\033[1;34m
CYAN		=		\033[1;36m
DEFAULT		=		\033[0m
SUPPR		=		\r\033[2K
NAME		=		IRC
BOT_NAME	=		Wall_E

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

MUTE			:=		1

IRC_PORT		=		6667
IRC_PASS		=		mdp

# --------------- FILES --------------- #

LIST_BOT_SRC	=	main.cpp

LIST_SRC		=	main.cpp				\
					parsingUtils.cpp		\
					server.cpp				\
					client.cpp				\
					clientCommand.cpp		\
					serverCommand.cpp		\
					serverUtils.cpp			\
					channel.cpp				\
					print.cpp				\
					serverLogs.cpp			\
					commands/join.cpp		\
					commands/mode.cpp		\
					commands/nick.cpp		\
					commands/part.cpp		\
					commands/pass.cpp		\
					commands/ping.cpp		\
					commands/privmsg.cpp	\
					commands/quit.cpp		\
					commands/user.cpp		\
					commands/kick.cpp		\
					commands/invite.cpp 	\
					commands/topic.cpp

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=		.build/
DIR_SRC			=		srcs/
BOT_DIR			=		srcs/bot/
DIR_INCLUDE		=		inc/

# ------------- SHORTCUTS ------------- #

OBJ					=	$(patsubst %.cpp, $(DIR_BUILD)%.o, $(SRC))
DEP					=	$(patsubst %.cpp, $(DIR_BUILD)%.d, $(SRC))
SRC					=	$(addprefix $(DIR_SRC),$(LIST_SRC))

BOT_OBJ				=	$(patsubst %.cpp, $(DIR_BUILD)%.o, $(BOT_SRC))
BOT_DEP				=	$(patsubst %.cpp, $(DIR_BUILD)%.d, $(BOT_SRC))
BOT_SRC				=	$(addprefix $(BOT_DIR),$(LIST_BOT_SRC))

# ------------ COMPILATION ------------ #

CPPFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g $(DEBUG_FLAG)

DEP_FLAGS		=	-MMD -MP

DEBUG_FLAG		=	-D DEBUG=1

CXX				=	c++

# -------------  COMMANDS ------------- #

RM				=	rm -rf

MKDIR			=	mkdir -p

START			=	$(NAME) $(IRC_PORT) $(IRC_PASS)

#***********************************  RULES  **********************************#

all:	header	$(NAME)	$(BOT_NAME)

# ---------- VARIABLES RULES ---------- #

$(BOT_NAME):	$(BOT_OBJ)
ifeq ($(MUTE),1)
	@$(CXX) $(CPPFLAGS) -o $(BOT_NAME) $(BOT_OBJ)
	@echo -n "${SUPPR} ${GREEN}	${BOT_NAME} : 🆗${DEFAULT}\n"
else
	$(CXX) $(CPPFLAGS) -o $(BOT_NAME) $(BOT_OBJ)
endif


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
	$(RM) .log

fclean:	clean
	$(RM) $(BOT_NAME)
	$(RM) $(NAME)

header:
	@echo "$$HEADER"

re:		fclean
	@$(MAKE) all --no-print-directory

start:
	@$(MAKE) all --no-print-directory
	./$(START)


.PHONY:	re clean fclean all header start
