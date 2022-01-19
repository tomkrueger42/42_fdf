# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2022/01/19 20:09:00 by tkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
GG		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	src/fdf.c
LIBFT	=	-L./lib/libft -lft lib/libft/libft.a
# MINILIBX =	-Lmlx -lmlx -framework OpenGL -framework AppKit mlx/libmlx.a

all: $(NAME)

$(NAME): libmake
	@$(CC) $(CFLAGS) $(SRC) $(MINILIBX) $(LIBFT) -o $(NAME)

libmake:
	@make -C lib/libft/
#	@make -C mlx/

clean:
	@rm -f *.o *~
	@make -C lib/libft/ clean
	@make -C mlx/ clean

fclean: clean
	@rm -f $(NAME)
	@rm -f lib/libft/libft.a
	@rm -f mlx/libmlx.a

re: fclean all

dbg: fclean
	$(CC) $(CFLAGS) -g $(SRC) $(MINILIBX) -o $(NAME)
	lldb fdf
