NAME= minishell
SRC_PATH= srcs
HDR_PATH= includes
OBJ_PATH= obj
LIB_PATH= libft


SRC_NAME=allocation.c\
		check.c\
		check2.c\
		check3.c\
		redirection_tools.c\
		redirection_tools2.c\
		sort.c\
		init.c\
		search_env.c\
		env.c\
		minishell.c\
		read_line.c\
		pwd.c\
		execute.c\
		tools.c\
    	directory.c\
		cd.c\
		shift.c\
		var_env.c\
		export.c\
		unset.c\
		pipes.c\
		export_sort.c\
		s_command.c\
		checkcmd.c\
		exit.c\
		execute_cmd.c\
		commade_effect.c\
		parse.c\
		free.c\
		ft_split_quotes.c\
		ft_space_split_quote.c\
		free_extended.c\
		echo.c\
		tools2.c\
		tools3.c\
		tools4.c\
		variables.c\
		back_slash.c\
		read_line_two.c\
		loop_shell.c\
		execute_cmd_two.c\
		export_extra.c\
		duping.c\
		variables2.c\
		variables3.c\

HDR_NAME=minishell.h 

OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

LIB= libft.a
FLAGS= -Wall -Wextra -Werror
LLIB_FLAG= -L$(LIB_PATH) libft/libft.a
H_FLAG= -I $(HDR_PATH)

COMP= gcc

all: lib  $(NAME) 

$(NAME) : $(LIB_PATH)/$(LIB) $(OBJ)
	@rm -rf minishell
	@$(COMP) -g $(H_FLAG) $(OBJ) $(LLIB_FLAG) -o $@
	@echo "													 Made by : \033[1;91mSqatim && helkhatr\033[m"
	@echo "      ___                       ___                       ___           ___           ___                                  "
	@echo "     /__/\        ___          /__/\        ___          /  /\         /__/\         /  /\                                 "
	@echo "    |  |::\      /  /\         \  \:\      /  /\        /  /:/_        \  \:\       /  /:/_                                "
	@echo "    |  |:|:\    /  /:/          \  \:\    /  /:/       /  /:/ /\        \__\:\     /  /:/ /\    ___     ___   ___     ___  "
	@echo "  __|__|:|\:\  /__/::\      _____\__\:\  /__/::\      /  /:/ /::\   ___ /  /::\   /  /:/ /:/_  /__/\   /  /\ /__/\   /  /\ "
	@echo " /__/::::| \:\ \__\/\:\__  /__/::::::::\ \__\/\:\__  /__/:/ /:/\:\ /__/\  /:/\:\ /__/:/ /:/ /\ \  \:\ /  /:/ \  \:\ /  /:/ "
	@echo " \  \:\~~\__\/    \  \:\/\ \  \:\~~\~~\/    \  \:\/\ \  \:\/:/~/:/ \  \:\/:/__\/ \  \:\/:/ /:/  \  \:\  /:/   \  \:\  /:/  "
	@echo "  \  \:\           \__\::/  \  \:\  ~~~      \__\::/  \  \::/ /:/   \  \::/       \  \::/ /:/    \  \:\/:/     \  \:\/:/   "
	@echo "   \  \:\          /__/:/    \  \:\          /__/:/    \__\/ /:/     \  \:\        \  \:\/:/      \  \::/       \  \::/    "
	@echo "    \  \:\         \__\/      \  \:\         \__\/       /__/:/       \  \:\        \  \::/        \__\/         \__\/     "
	@echo "     \__\/                     \__\/                     \__\/         \__\/         \__\/                                 "
	@echo "						Compilation of $(NAME):  \033[1;32mOK\033[m"

lib:
	@make -sC $(LIB_PATH)

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) -g $(FLAGS) $(H_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIB_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_PATH)
	@echo "\033[0;31m>> $(NAME) && all obbjects are deleted.\033[0m" 

re : fclean all
