/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/23 19:17:24 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>


void	*make_map(t_list *map, char *file)
{
	int		fd;
	char	*line;
	int		counter;
	int		n_nbrs;

	fd = open(file, O_RDONLY);
	line = NULL;
	counter = 0;
	n_nbrs = -1;
	while (line != NULL || counter == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (n_nbrs == -1)
		{
			n_nbrs = ft_count_char(line, ' ');
			ft_lstadd_back(&map, ft_lstnew(&n_nbrs));
		}
		ft_lstadd_back(&map, ft_lstnew(ft_getnbrs(line)));
		free(line);
		counter++;
	}
	close(fd);
	return (map);
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

	map = NULL;
	map = make_map(map, "fdf.txt");
	
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_X, WIN_Y, "fdf");
	img.img = mlx_new_image(vars.mlx, WIN_X, WIN_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	img = draw_wireframe(map, img);
	mlx_put_image_to_window(vars.mlx, vars.win, &img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
