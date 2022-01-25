/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 22:30:50 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/25 19:55:01 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_data	draw_wireframe(t_list *map, t_data img)
{
	t_px	*origin;
	int		x_distance;
	int		y_distance;
	
	x_distance = IMG_X / (ft_lstsize(map) + WIDTH);
	y_distance = IMG_Y / (ft_lstsize(map) + WIDTH);
	origin = set_px(y_distance * ft_lstsize(map), 1, 0x00FFFFFF);
	/* needs some kind of loop to parse the map and draw */
	draw_line(&img, origin, set_px(origin->x + x_distance, origin->y + y_distance, 0x00FFFFFF));
	return (img);
}

t_px	*set_px(int x, int y, int color)
{
	t_px	*new;

	new = malloc(sizeof(struct s_px) * 1);
	new->x = x;
	new->y = y;
	new->color = color;
	return (new);
}

void	draw_line(t_data *img, t_px *start, t_px *end)
{
	float	x;
	float	y;
	float	xy_ratio;

	x = end->x - start->x;
	y = end->y - start->y;
	xy_ratio = x / y;
	while (x > 0 && y > 0)
	{
		if (x / y > xy_ratio)
		{
			my_mlx_pixel_put(img, start->x + x, start->y + y, 0x00FFFFFF);
			x--;
		}
		else
		{
			my_mlx_pixel_put(img, start->x + x, start->y + y, 0x00FFFFFF);
			y--;
		}
	}
	free(start);
	free(end);
	start = NULL;
	end = NULL;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
