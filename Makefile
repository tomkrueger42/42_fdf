# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2022/01/06 21:08:51 by tkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
GG		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	src/fdf.c
MINILIBX =	-Lmlx -lmlx -framework OpenGL -framework AppKit mlx/libmlx.a

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(SRC) $(MINILIBX) -o $(NAME)

libmake:
	@make -C mlx/

clean:
	@rm -f *.o *~
	@make -C mlx/ clean

fclean: clean
	@rm -f $(NAME)
#	@make -C mlx/ fclean

re: fclean all

dbg: fclean
	$(CC) $(CFLAGS) -g $(SRC) $(MINILIBX) -o $(NAME)
	lldb fdf
# **************************************************************************** #
#	Project specific														   #
# **************************************************************************** #

