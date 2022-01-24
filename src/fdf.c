/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/24 22:09:07 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>


t_list	*make_map(t_list *map, char *file)
{
	int		fd;
	char	*line;
	int		counter;
	int		n_nbrs;

	fd = open(file, O_RDONLY);
	line = NULL;
	n_nbrs = -1;
	while (line != NULL || n_nbrs == -1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (n_nbrs == -1)
		{
			n_nbrs = ft_count_char(line, ' ') + 1;
			map = ft_lstnew(&n_nbrs);
		}
		int *arr = ft_getnbrs(line);
		printf("make_map %i\n", arr[0]);
		printf("make_map %i\n", arr[1]);
		printf("make_map %i\n", arr[2]);
		printf("make_map %i\n", arr[3]);
		ft_lstadd_back(&map, ft_lstnew(ft_getnbrs(line)));
		free(line);
	}
	close(fd);
	printf("x: %i\n", map->content[0]);
	printf("y: %i\n", ft_lstsize(map));
	return (map);
}

void	print_map(t_list *map)
{
	t_list	*tmp;
	int		i;

	tmp = map;
	while (tmp != NULL)
	{
		printf("A\n");
		i = 0;
		while (i < map->content[0])
		{
			printf("i: %i\n", i);
			printf("%i ", tmp->content[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

int	key_hook(int keycode, void	*mlx, void *win)
{
	printf("keycode: %i\n", keycode);
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(mlx, win);
		exit(0);
	}
	return (0);
}

int	main(__unused int argc, __unused char **argv)
{
	t_list	*map;
	t_vars	vars;
	t_data	img;

	map = make_map(map, "fdf.txt");
	print_map(map);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_X, WIN_Y, "fdf");
	img.img = mlx_new_image(vars.mlx, WIN_X, WIN_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("segfault\n");
	//img = draw_wireframe(map, img);
	//mlx_put_image_to_window(vars.mlx, vars.win, &img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}

/* int	**arr_map(int **arr_map, char *file)
{
	int	fd;
	int	x;
	int	y;
	char	*line;
	
	fd = open(file, O_RDONLY);
	y = 0;
	while (line != NULL || y == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		x = ft_count_char(line, ' ');
		if (line != NULL)
			free(line);
		y++;
	}
	printf("0\n");
	close(fd);
	printf("1\n");
	arr_map = ft_calloc(sizeof(int), x * y);
	fd = open(file, O_RDONLY);
	y = 0;
	while (line != NULL || y == 0)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		arr_map[y] = ft_getnbrs(line);
		y++;
	}
	close(fd);
	printf("2\n");
	int i = 0;
	int j;
	printf("xy %i%i\n", x, y);
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("3\n");
			printf("%i ", arr_map[x][y]);
			j++;
		}
		printf("\n");
		i++;
	}
} */