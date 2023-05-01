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

FILES 		= 	ft_atoi \
				ft_atof \
				ft_atoll \
				ft_bzero \
				ft_calloc \
				ft_isalnum \
				ft_isalpha \
				ft_isascii \
				ft_isdigit \
				ft_isprint \
				ft_itoa \
				ft_memchr \
				ft_memcmp \
				ft_memcpy \
				ft_memmove \
				ft_memset \
				ft_putchar_fd\
				ft_putendl_fd \
				ft_putint_fd \
				ft_putuint_fd \
				ft_putstr_fd \
				ft_split \
				ft_strchr \
				ft_strdup \
				ft_strndup \
				ft_striteri \
				ft_strjoin \
				ft_strjoinf \
				ft_strlcat \
				ft_strlcpy \
				ft_strlen \
				ft_strlenc \
				ft_strmapi \
				ft_strncmp \
				ft_strnstr \
				ft_strrchr \
				ft_strtrim \
				ft_substr \
				ft_tolower \
				ft_toupper \
				ft_putnbrbase_fd \
				ft_putptraddr_fd \
				ft_printf \
				ft_get_next_line \
				ft_realloc\
				ft_lstadd_back \
				ft_lstadd_front \
				ft_lstclear \
				ft_lstdelone \
				ft_lstiter \
				ft_lstlast \
				ft_lstmap \
				ft_lstnew \
				ft_lstsize \
 
SRCS 		= 	$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(FILES)))
OBJS 		= 	$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(FILES)))
INCL		=	./include/libft.h

NAME = libft.a
FLAGS = -Wall -Werror -Wextra
 
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCL)
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@cc $(FLAGS) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

clean:
	@echo "$(BLUE)[$(NAME)] Deleting all objects $(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
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