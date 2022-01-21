/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/21 23:15:03 by tkruger          ###   ########.fr       */
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

int	main(__unused int argc, __unused char **argv)
{
	t_list	*map;
/* 	void	*mlx;
	void	*mlx_win; */

	map = NULL;
	map = make_map(map, "fdf.txt");
/* 
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx); */

	return (0);
}
