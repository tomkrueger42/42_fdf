/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/09 15:58:31 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>

t_list	*make_map(t_fdf *fdf, t_list *map, char *file)
{
	int		fd;
	char	*line;
	int		*nbrs;

	fd = open(file, O_RDONLY);
	line = NULL;
	fdf->width = -1;
	while (line != NULL || fdf->width == -1)
	{
		line = get_next_line(fd);
		if (line == NULL && fdf->width != -1)
			break ;
		fdf->width = ft_count_char(line, ' ') + 1;
		nbrs = ft_getnbrs_free(ft_split(ft_strtrim(line, "\n"), ' '));
		ft_lstadd_back(&map, ft_lstnew(nbrs));
		free(line);
	}
	close(fd);
	fdf->length = ft_lstsize(map);
	return (map);
}

void	print_map(t_fdf *fdf, t_list *map)
{
	int		i;

	if (map == NULL)
		return ;
	while (map != NULL)
	{
		i = 0;
		while (i < fdf->width)
		{
			printf("%i ", map->content[i]);
			i++;
		}
		printf("\n");
		map = map->next;
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
	t_fdf	*fdf;
	t_vars	vars;
	t_data	img;

	map = NULL;
	fdf = ft_calloc(1, sizeof(struct s_fdf));
	if (fdf == NULL)
		return (0);
	map = make_map(fdf, map, "fdf.txt");
	// print_map(fdf, map);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_X, WIN_Y, "fdf");
	img.img = mlx_new_image(vars.mlx, IMG_X, IMG_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
									&img.line_length, &img.endian);
	printf("window opened\n");
	draw_wireframe(fdf, map, &img);
	printf("draw_wireframe() completed\n");
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, (WIN_X - IMG_X) / 2, (WIN_Y - IMG_Y) / 2);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
