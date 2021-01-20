NAME= minishell
SRC_PATH= srcs
HDR_PATH= includes
OBJ_PATH= obj
LIB_PATH= libft


SRC_NAME=init.c\
		search_env.c\
		env.c\
		minishell.c\
		read_line.c\
		pwd.c\
		execute.c\
		tools.c\
    	directory.c\
		parse.c\
		cd.c\
		shift.c\
		var_env.c\
		export.c\
		unset.c\
		pipes.c\
		read.c\
		lanch.c\
		parsing.c\
		get_next_line.c\
		get_next_line_utils.c\
		ft_space_split.c\
		ft_char_split.c\
		pipe.c\
		check_built.c\
		echo.c\
		condition_check_0.c\
		condition_check_1.c\
		condition_check_2.c\
		details.c\
		is_in_redirection.c\
		is_after_redirection.c\
		is_before_redirection.c\
		errors.c\
		comand_details.c\
		redirection_filename.c\
		sort_seperators_all.c\
		test.c\
		minishell_space.c\
		minishell_split.c\
		tools1.c\
		redirections_quote.c\
	 	list_creat.c\
		list_add.c\
		list_modify.c\
		print.c\
		simple_cmd_pars.c\
		pars_conditions.c\
		concats.c\
		redirection_sign.c\
		pipe_sort.c\
		comma_sort.c\
		main.c\


HDR_NAME=minishell.h 

OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

LIB= libft.a
FLAGS= 
LLIB_FLAG= -L$(LIB_PATH) libft/libft.a
H_FLAG= -I $(HDR_PATH)

COMP= gcc

all: lib  $(NAME) 

$(NAME) : $(LIB_PATH)/$(LIB) $(OBJ)
	@rm -rf miniRT
	@$(COMP) $(H_FLAG) $(LLIB_FLAG) $(OBJ) -o $@

lib:
	@make -sC $(LIB_PATH)

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) $(FLAGS) $(H_FLAG)  -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIB_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_PATH)
	@echo "\033[0;31m>> $(NAME) && all obbjects are deleted.\033[0m" 

re : fclean all
