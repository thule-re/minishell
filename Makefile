RESET		=	\033[0m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RED			=	\033[31m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
UP			=	\033[A
CUT			=	\033[K

SRC_DIR 	=	./src
OBJ_DIR 	=	./obj
INC_DIR		=	include
OBJ_DIRS 	=	./obj \
				./obj/builtins \
				./obj/env \
				./obj/execution \
				./obj/input \
				./obj/main_and_error \
				./obj/misc_utils \
				./obj/parsing \
				./obj/signals \
				./obj/malloc \

FILES 		=	builtins/builtin_utils \
				builtins/cd \
				builtins/echo \
				builtins/env \
				builtins/exit \
				builtins/export \
				builtins/export_utils \
				builtins/pwd \
				builtins/unset \
				env/env_utils \
				env/export_env \
				env/init_env \
				execution/pipex_children \
				execution/run_commands \
				execution/pipe_utils \
				input/get_input \
				input/make_input \
				main_and_error/error \
				main_and_error/free \
				main_and_error/main \
				main_and_error/syntax_error \
				misc_utils/array_utils \
				misc_utils/string_utils \
				parsing/ft_shell_split \
				parsing/heredoc_parsing \
				parsing/pre_parsing \
				parsing/shell_split_utils \
				parsing/shell_split_utils_2 \
				signals/signals \
				malloc/malloc

INCL		=	./include/minishell.h

SRCS 		= 	$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(FILES)))
OBJS 		= 	$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(FILES)))

INCLUDE		=	-I $(HOME)/goinfre/.brew/opt/readline/include/
LIBS		=	-L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

NAME		=	minishell
LIBFT_DIR	=	./libft
LIBFT		=	./libft/libft.a
FLAGS		=	-Wall -Werror -Wextra
 
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@cc $(FLAGS) $(INCLUDE) $(LIBS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

$(LIBFT):
	@+make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCL)
	@mkdir -p $(OBJ_DIRS)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@cc $(FLAGS) -o $@ -c $< -I $(INC_DIR)
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

clean:
	@+make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(BLUE)[$(NAME)] Deleting all objects $(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)Deleting $(LIBFT) $(RESET)"
	@rm -f $(LIBFT)
	@echo "$(BLUE)Deleting $(NAME) $(RESET)"
	@rm -f $(NAME)

re: fclean all

coffee:
	@clear
	@echo ""
	@echo "                   ("
	@echo "	                     )     ("
	@echo "               ___...(-------)-....___"
	@echo '           .-""       )    (          ""-.'
	@echo "      .-''''|-._             )         _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |          :::      ::::::::  |"
	@echo "     \  \   |        :+:      :+:    :+:  |"
	@echo "      '\ '\ |      +:+ +:+         +:+    |"
	@echo "        '\ '|    +#+  +:+       +#+       |"
	@echo "        _/ /\  +#+#+#+#+#+   +#+          /"
	@echo "       (__/  \      #+#    #+#           /"
	@echo '    _..---""` \    ###   ########.fr    /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "                 ("
	@echo "	                  )      ("
	@echo "               ___..(.------)--....___"
	@echo '           .-""       )   (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |          :::      ::::::::  |"
	@echo "     \  \   |        :+:      :+:    :+:  |"
	@echo "      '\ '\ |      +:+ +:+         +:+    |"
	@echo "        '\ '|    +#+  +:+       +#+       |"
	@echo "        _/ /\  +#+#+#+#+#+   +#+          /"
	@echo "       (__/  \      #+#    #+#           /"
	@echo '    _..---""` \    ###   ########.fr    /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "               ("
	@echo "	                  )     ("
	@echo "               ___..(.------)--....___"
	@echo '           .-""      )    (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |          :::      ::::::::  |"
	@echo "     \  \   |        :+:      :+:    :+:  |"
	@echo "      '\ '\ |      +:+ +:+         +:+    |"
	@echo "        '\ '|    +#+  +:+       +#+       |"
	@echo "        _/ /\  +#+#+#+#+#+   +#+          /"
	@echo "       (__/  \      #+#    #+#           /"
	@echo '    _..---""` \    ###   ########.fr    /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "             (         ) "
	@echo "	              )        ("
	@echo "               ___)...----)----....___"
	@echo '           .-""      )    (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |          :::      ::::::::  |"
	@echo "     \  \   |        :+:      :+:    :+:  |"
	@echo "      '\ '\ |      +:+ +:+         +:+    |"
	@echo "        '\ '|    +#+  +:+       +#+       |"
	@echo "        _/ /\  +#+#+#+#+#+   +#+          /"
	@echo "       (__/  \      #+#    #+#           /"
	@echo '    _..---""` \    ###   ########.fr    /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
