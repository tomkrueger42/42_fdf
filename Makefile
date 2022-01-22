# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2022/01/22 21:11:46 by tkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	./inc/fdf.h
SRC_PATH =	./src/
SRCS	=	fdf.c image.c
OBJ_PATH =	./objs/
OBJS	=	$(patsubst %c,$(OBJ_PATH)%o,$(SRCS))
LIBFT	=	-L./lib/libft -lft lib/libft/libft.a
MINILIBX =	-Lmlx -lmlx -framework OpenGL -framework AppKit mlx/libmlx.a
LIBS	=	$(LIBFT) $(MINILIBX)

.PHONY: all $(NAME) $(OBJ_PATH) libmake clean fclean re dbg asan

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS) libmake
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

libmake:
	@make -C lib/libft/
	@make -C mlx/

clean:
	@rm -rf $(OBJ_PATH)
	@rm -f *.o *~
	@make -C lib/libft/ clean
	@make -C mlx/ clean
	@echo "\033[1;32m.o files removed!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f lib/libft/libft.a
	@rm -f mlx/libmlx.a
	@echo "\033[1;32mbinary files removed!\033[0m" 

re: fclean all

dbg: fclean libmake
	$(CC) $(CFLAGS) -g $(SRC) $(LIBFT) -o $(NAME)
	lldb fdf fdf.txt

asan: fclean libmake
	$(CC) $(CFLAGS) -fsanitize=address $(SRC) $(LIBFT) -o $(NAME)