/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 22:30:50 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/24 21:15:30 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	get_value(t_list *map_node, int pos)
{
	/* int	value;

	value = map_node->content[pos];
	return (value); */
}

t_data	draw_wireframe(t_list *map, t_data img)
{
	/* int *i = map->content;
	
	printf("n_x: %p\n", map->content);
	printf("n_x: %p\n", (int *)map->content);
	printf("n_x: %i\n", *i);
	printf("n_x: %i\n", get_value(map, 0)); */
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
