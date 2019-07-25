# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aclecler <aclecler@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 00:39:00 by aclecler          #+#    #+#              #
#    Updated: 2019/03/15 10:29:15 by dazheng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

CC = gcc

# FLAGS = -O3 -Wall -Wextra -Werror

IN =	asm.c\
		error.c\
		free_all.c\
		init.c\
		handle_arg.c\
		label.c\
		label_management.c\
		label_tools.c\
		op_fct.c\
		op_fct2.c\
		op_fct3.c\
		op_fct4.c\
		parsing.c\
		parse_instructions.c\
		tools.c\
		write_cor_file.c

LIBFT = ../libftprintf

SRCS_DIR = srcs

OUT_DIR = tmp

INC = -Iincludes -I ../libftprintf/includes/ -I $(LIBFT)/libft/includes


SRCS_LEMIN = $(addprefix $(SRCS_DIR)/,$(IN))

OBJS_LEMIN = $(addprefix $(OUT_DIR)/,$(IN:.c=.o))

all: $(NAME)

$(NAME): $(OBJS_LEMIN)
	@make -C $(LIBFT)
	@$(CC) $(FLAGS) $^ -o $@ -I $(LIBFT)/libft/includes -I $(INC) $(LIBFT)/libftprintf.a
	@cp $(NAME) ../
	@echo "\033[32mOutfile ASM	[ ✔ ]\e[0m"

$(OUT_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OUT_DIR)
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

norme:
	norminette ./$(LIBFT)/ ./$(INC)/ ./$(SRCS_DIR)/
	@echo

clean:
	@rm -f $(OBJS_LEMIN)
	@rm -rf $(OUT_DIR)
	@make clean -C $(LIBFT)
	@echo "\033[32mClean  [ ✔ ]\e[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f ../$(NAME)
	@make fclean -C $(LIBFT)
	@echo "\033[32mFclean  [ ✔ ]\e[0m"

re: fclean all
m : fclean main

f: fclean
r: re
c: clean
