/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/18 12:39:59 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>


#include <stdio.h>

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
		if (line == NULL)
			break ;
		if (fdf->width == -1)
			fdf->width = ft_count_nbrs(line);
		if (ft_count_nbrs(line) == 0)
			break ;
		nbrs = ft_getnbrs_free(ft_split_free(ft_strtrim_free(line, "\n"), ' '));
		ft_lstadd_back(&map, ft_lstnew(nbrs));
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

	if (keycode == ESC_KEY)
	{
		system("leaks fdf");
		exit(0);
	}
	return (0);
}

void set_fdf(t_fdf *fdf, t_list *map)
{
	size_t	i;

	while (map != NULL)
	{
		i = 0;
		while (i < fdf->width)
		{
			if (fdf->max_height < ft_abs(map->content[i]))
				fdf->max_height = ft_abs(map->content[i]);
			i++;
		}
		map = map->next;
	}
	if (fdf->max_height == 0)
		fdf->max_height = 1;
	fdf->px_dist = ft_min(2, WIN_X, WIN_Y) / (fdf->width + fdf->length / ROTATION);
}

int	main(int argc, char **argv)
{
	t_list	*map;
	t_fdf	*fdf;
	t_vars	vars;

	map = NULL;
	if (argc != 2)
		return (ft_putstr_fd("./fdf <filename>\n", 2));
	fdf = ft_calloc(1, sizeof(struct s_fdf));
	if (fdf == NULL)
		return (0);
	// vars = ft_calloc(1, sizeof(struct s_vars));
	// if (vars == NULL)
	// {
	// 	free(fdf);
	// 	fdf = NULL;
	// 	return (0);
	// }
	// fdf->vars = vars;
	map = make_map(fdf, map, argv[1]);
	if (map == NULL)
		return (0);
	// print_map(fdf, map);
	set_fdf(fdf, map);
	fdf->vars.mlx = mlx_init();
	fdf->vars.win = mlx_new_window(fdf->vars.mlx, WIN_X, WIN_Y, "fdf");
	fdf->img.img = mlx_new_image(fdf->vars.mlx, WIN_X, WIN_Y);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
									&fdf->img.line_length, &fdf->img.endian);
	draw_wireframe(fdf, map);
	mlx_put_image_to_window(fdf->vars.mlx, fdf->vars.win, fdf->img.img, 0, 0);
	mlx_key_hook(fdf->vars.win, key_hook, &fdf->vars);
	mlx_loop(fdf->vars.mlx);
	return (0);
}
