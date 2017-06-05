# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/17 18:17:30 by jecarol           #+#    #+#              #
#    Updated: 2017/06/05 18:16:41 by jecarol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS_LIST = main.c ft_arrows.c ft_sig_mngmnt.c ft_print_section.c\
			ft_mng_elements.c ft_core.c ft_setup.c ft_exit.c ft_select_elem.c
SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objs/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

HEADERS = -I./libft -I./includes

LIB = -L./libft -lft

# COLOR
C_GOOD = "\033[32m"
C_DURING = "\033[36m"

# MESSAGE
SUCCESS = $(C_GOOD)COMPILATION SUCCEEDED

all: $(NAME)

$(NAME): $(OBJS)
	@make re -C ./libft/
	@echo $(C_DURING)"Compiling" [ $(NAME) . . . ]
	@$(CC) $(CFLAGS) $^ $(LIB) -o $@ -ltermcap
	@echo $(SUCCESS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
		@/bin/rm -rf $(OBJS_DIR) $(NAME).dSYM
		@make clean -C libft/
		@echo $(C_GOOD)"OBJ FILES && DEBUG FOLDER DELETED"

fclean: clean
		@/bin/rm -rf $(NAME)
		@make fclean -C libft/
		@echo $(C_GOOD)"EXECUTABLE FILE DELETED"

re: fclean all
