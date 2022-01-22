/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/22 22:53:18 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>


void	*make_map(t_list *map, char *file)
{
	int				fd;
	char			*line;
	int				counter;
	
	
	fd = open(file, O_RDONLY);
	line = NULL;
	counter = 0;
	while (line != NULL || counter == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
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
	if (keycode == 53)
	{
		mlx_destroy_window(mlx, win);
		exit(0);
	}
	return (0);
}

int	main(__unused int argc, __unused char **argv)
{
	t_vars	*vars;
	t_list	*map;
	void	*mlx_img;

	map = NULL;
	map = make_map(map, "fdf.txt");

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "fdf");
	
	mlx_key_hook(vars->win, key_hook, &vars);
	mlx_loop(vars->mlx);

	return (0);
}
