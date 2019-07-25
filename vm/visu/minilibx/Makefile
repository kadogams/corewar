# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adefonta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/22 16:07:05 by adefonta          #+#    #+#              #
#    Updated: 2018/07/22 16:14:18 by adefonta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOM=libmlx.a

SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c


OBJ= mlx_shaders.o mlx_new_window.o mlx_init_loop.o mlx_new_image.o mlx_xpm.o mlx_int_str_to_wordtab.o

FLAG = -Wall -Werror -Wextra

all: $(NOM)

$(NOM):	$(OBJ)
	@gcc -c $(SRC)
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NOM)
	
re: clean all
