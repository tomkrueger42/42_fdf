# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2022/01/21 22:31:16 by tkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
GG		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	src/fdf.c src/image.c
LIBFT	=	-L./lib/libft -lft lib/libft/libft.a
# MINILIBX =	-Lmlx -lmlx -framework OpenGL -framework AppKit mlx/libmlx.a

all: $(NAME)

$(NAME): libmake
	@$(CC) $(CFLAGS) $(SRC) $(MINILIBX) $(LIBFT) -o $(NAME)

libmake:
	@make -C lib/libft/
	@make -C lib/libft/ clean
#	@make -C mlx/
#	@make -C mlx/ clean

clean:
	@rm -f *.o *~
	@make -C lib/libft/ clean
	@make -C mlx/ clean

fclean: clean
	@rm -f $(NAME)
	@rm -f lib/libft/libft.a
	@rm -f mlx/libmlx.a

re: fclean all

dbg: fclean libmake
	$(CC) $(CFLAGS) -g $(SRC) $(LIBFT) -o $(NAME)
	lldb fdf fdf.txt

asan: fclean libmake
	$(CC) $(CFLAGS) -fsanitize=address $(SRC) $(LIBFT) -o $(NAME)