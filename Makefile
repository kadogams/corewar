# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazheng <dazheng@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/12 13:38:06 by dazheng           #+#    #+#              #
#    Updated: 2019/03/12 15:34:17 by adefonta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parse
NAME2 = vm

all:
	@make -C $(NAME)
	@make -C $(NAME2)

clean:
	@make clean -C $(NAME)
	@make clean -C $(NAME2)

fclean:
	@make fclean -C $(NAME)
	@make fclean -C $(NAME2)

re: fclean all

.PHONY: re clean fclean all
