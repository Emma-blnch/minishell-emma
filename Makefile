# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/02/27 09:54:42 by ema_blnch        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#		General variables													   #
# **************************************************************************** #

NAME		= minishell

MAKEFLAGS += --no-print-directory

DIR_SRC		= src
DIR_EXEC	= execution
DIR_PARS	= parsing
DIR_BUTI	= builtins

DIR_OBJ		= obj
DIR_OBJS	= $(DIR_OBJ) $(DIR_OBJ)/$(DIR_EXEC) $(DIR_OBJ)/$(DIR_PARS) $(DIR_OBJ)/$(DIR_BUTI)

DIR_INC		= inc

DIR_LIB		= $(DIR_INC)/libft

HEADER		= $(DIR_INC)/minishell.h

# FUNC_EXEC	= 	execution.c \
# 				readability.c \
# 				redirection.c \
# 				path.c \
# 				setup.c \
# 				heredoc.c \
# 				errors.c \
# 				ast.c

FUNC_EXEC	=	exec.c \
				exec2.c \
				find_cmd.c \
				here_doc.c \
				launch_builtin.c \
				utils.c
				
FUNC_PARS	=	cleanup.c \
				cmd_fd.c \
				cmd_utils.c \
				dollar_utils.c \
				errors.c \
				errors2.c \
				manage_dollar.c \
				parse_cmd.c \
				quote.c \
				readline.c \
				signals.c \
				signals2.c \
				token_utils.c \
				token.c \
				list_utils.c \

FUNC_BUTI	=	cd.c \
				cd_utils.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				export_utils.c \
				pwd.c \
				unset.c \

FUNC		= 	$(addprefix $(DIR_EXEC)/, $(FUNC_EXEC)) \
				$(addprefix $(DIR_PARS)/, $(FUNC_PARS)) \
				$(addprefix $(DIR_BUTI)/, $(FUNC_BUTI)) \

MAIN		= main.c

SRC			= 	$(addprefix $(DIR_SRC)/, $(FUNC)) \
				$(addprefix $(DIR_SRC)/, $(MAIN))

OBJ			= $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

LIB			= $(DIR_LIB)/libft.a

DEP			= $(LIB) $(DIR_OBJS) $(HEADER)

INC			= -I$(DIR_INC) -I$(DIR_LIB)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

DEF_COLOR	= \033[0;39m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m

# **************************************************************************** #
#		Unit test variables													   #
# **************************************************************************** #

T_NAME		= utest

T_DIR		= test

T_SRC		= utest.c

T_OBJ		= utest.o

T_INC		= -I$(HOME)/Criterion/include/ \
				-I$(HOME)/Criterion/ \
				$(INC)

T_LIB		= -Wl,-rpath=$(HOME)/Criterion/build/src \
				-L$(HOME)/Criterion/build/src \
				-L$(HOME)/Criterion \
				-lcriterion \
				-L$(DIR_LIB) -lft -lreadline

T_CC		= $(CC) $(CFLAGS) $(T_INC) -g

T_EXCL		= obj/main.o

V_FLAG		= valgrind --leak-check=full --show-leak-kinds=all \
				--track-origins=yes --trace-children=yes --track-fds=yes \
				--suppressions=inc/readline.supp

# **************************************************************************** #
#																			   #
#			COMPILATION														   #
#																			   #
# **************************************************************************** #

all:				$(NAME)

$(NAME):			$(DEP) $(OBJ)
					$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) -L$(DIR_LIB) \
					-lft -lreadline
					@echo "$(GREEN)Minishell Compiled!$(DEF_COLOR)"

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o  $@

$(DIR_OBJS):
					mkdir -p $@

$(LIB):
					make -C $(DIR_LIB)


# **************************************************************************** #
#																			   #
#			TEST AND DEBUG													   #
#																			   #
# **************************************************************************** #

debug:		$(DEP) $(OBJ)
			@echo "Compiling with debug flag"
			$(CC) $(CFLAGS) -g $(INC) -o $(NAME) $(SRC) -L$(DIR_LIB) \
			-lft -lreadline

$(T_NAME):	$(DEP) $(OBJ)
			@echo "Compiling unit test"
			$(T_CC) $(LIB) $(T_LIB) $(filter-out $(T_EXCL), $(OBJ)) \
			$(addprefix $(T_DIR)/, $(T_SRC)) -o $(T_DIR)/$(T_NAME) -L$(DIR_LIB) \
			-lft -lreadline

test:		$(T_NAME)
			@echo "Running unit tests :"
			./$(T_DIR)/$(T_NAME)

valgrind:	$(NAME)
			@echo "Running with valgrind :"
			$(V_FLAG) ./$(NAME)

# **************************************************************************** #
#																			   #
#			CLEAN UP														   #
#																			   #
# **************************************************************************** #

clean:
			rm -rf $(DIR_OBJ)
			rm -rf $(T_DIR)/$(T_NAME)
			make -C $(DIR_LIB) clean
			@echo "$(MAGENTA)Minishell objects cleaned !$(DEF_COLOR)"

fclean:
			rm -rf $(DIR_OBJ)
			rm -rf $(T_DIR)/$(T_NAME)
			rm -rf $(NAME)
			make -C $(DIR_LIB) fclean
			@echo "$(YELLOW)Minishell cleaned !$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt !$(DEF_COLOR)"

.PHONY:		all clean fclean re debug test compile
