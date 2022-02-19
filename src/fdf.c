/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/19 17:06:49 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>


#include <stdio.h>

int	*extract_values(char **splitted)
{
	int		*nbrs;
	size_t	splitted_len;
	size_t	i;

	if (splitted == NULL)
		return (NULL);
	nbrs = ft_calloc(ft_arrlen(splitted) * 2, sizeof(*nbrs));
	if (nbrs == NULL)
		return (NULL);
	i = 0;
	splitted_len = ft_arrlen(splitted);
	while (i < splitted_len * 2)
	{
		nbrs[i] = ft_atoi(splitted[i / 2]);
		i++;
		if (ft_strchr(splitted[i / 2], ',') == NULL)
			nbrs[i] = -1;
		else
			nbrs[i] = ft_atoi_base(ft_strchr(splitted[i / 2], ',') + 3, 16);
		free(splitted[i / 2]);
		splitted[i++ / 2] = NULL;
	}
	free(splitted);
	splitted = NULL;
	return (nbrs);
}

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
			fdf->width = (ft_count_nbrs(line) - ft_count_char(line, ',')) * 2;
		nbrs = extract_values(ft_split_free(ft_strtrim_free(line, "\n"), ' '));
		ft_lstadd_back(&map, ft_lstnew(nbrs));
	}
	close(fd);
	fdf->length = ft_lstsize(map);
	return (map);
}

void	print_map(t_fdf *fdf, t_list *map)
{
	int	i;
	int	c = 0;

	if (map == NULL)
		return ;
	while (map != NULL)
	{
		i = 0;
		while (i < fdf->width)
		{
			printf(" %i,", map->content[i]);
			i++;
			printf("%x", map->content[i]);
			i++;
		}
		printf("\n");
		map = map->next;
		// printf("count: %i\n", c++);
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
	t_list	*parser;

	parser = map;
	fdf->max_height = 1;
	while (parser != NULL)
	{
		i = 0;
		while (i < fdf->width)
		{
			if (fdf->max_height < ft_abs(parser->content[i++]))
				fdf->max_height = ft_abs(parser->content[i - 1]);
			if (parser->content[i++] == -1)
				parser->content[i - 1] = CVOID;
		}
		parser = parser->next;
	}
	parser = map;
	while (parser != NULL)
	{
		i = 0;
		while (i++ < fdf->width)
			parser->content[i++ - 1] *= MHGHT / fdf->max_height;
		parser = parser->next;
	}
	fdf->px_dist = ft_min(2, WIN_X, WIN_Y) / (fdf->width / 2 + fdf->length * WARP / 100 / ROTATION);
	if (fdf->px_dist < 2)
		fdf->px_dist = 2;
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
	set_fdf(fdf, map);
	printf("width: %i, length: %i\n", fdf->width, fdf->length);
	// print_map(fdf, map);
	fdf->vars.mlx = mlx_init();
	fdf->vars.win = mlx_new_window(fdf->vars.mlx, WIN_X, WIN_Y, "fdf");
	fdf->img.img = mlx_new_image(fdf->vars.mlx, WIN_X * 2, WIN_Y * 2);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
									&fdf->img.line_length, &fdf->img.endian);
	draw_wireframe(fdf, map);
	mlx_put_image_to_window(fdf->vars.mlx, fdf->vars.win, fdf->img.img, 0, 0);
	mlx_key_hook(fdf->vars.win, key_hook, &fdf->vars);
	mlx_loop(fdf->vars.mlx);
	return (0);
}
