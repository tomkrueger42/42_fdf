/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 22:30:50 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/03 23:43:04 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

#define ROTATION 2
#define WARP 70

void	draw_wireframe(t_list *map, t_data *img)
{
	t_px	*origin;
	t_px	*cur;
	int		x_count;
	int		y_count;
	int		px_distance;
	t_list	*parser;
	int		height;

	y_count = 0;
	parser = map;
	px_distance = ft_min(2, IMG_X, IMG_Y) / sqrt( pow(WIDTH - 1, 2) + pow(ft_lstsize(map), 2));
	origin = set_px(ft_lstsize(map) * px_distance / ROTATION, parser->content[0] * 10, 0x00FFFFFF);
	
	while (y_count < ft_lstsize(map))
	{
		x_count = 0;
		cur = set_px(origin->x, origin->y - parser->content[0] * 10, origin->color);
		while (x_count < WIDTH - 1)
		{
			// y-lines
			if (y_count < ft_lstsize(map) - 1)
			{
				height = parser->content[x_count] - parser->next->content[x_count];
				draw_line(img, cur, set_px(cur->x - (px_distance / ROTATION), cur->y + (px_distance * WARP / 100) + height * 10, cur->color));
			}
			// x-lines
			height = parser->content[x_count] - parser->content[x_count + 1];
			draw_line(img, cur, set_px(cur->x + px_distance, cur->y + (px_distance / ROTATION * WARP / 100) + height * 10, 0x00FFFFFF));
			cur->x += px_distance;
			cur->y += (px_distance / ROTATION) * WARP / 100 + height * 10;
			x_count++;
		}
		// last y-line
		if (y_count < ft_lstsize(map) - 1)
		{
			height = parser->content[x_count] - parser->next->content[x_count];
			draw_line(img, cur, set_px(cur->x - (px_distance / ROTATION), cur->y + px_distance * WARP / 100 + height * 10, 0x00FFFFFF));
		}
		origin->x -= (px_distance / ROTATION);
		origin->y += px_distance * WARP / 100;
		parser = parser->next;
		y_count++;
	}
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
	double	x;
	double	y;
	double	xy_ratio;

	x = end->x - start->x;
	y = end->y - start->y;
	xy_ratio = x / y;
	while (x != 0 && y != 0)
	{
		if ((x / y > xy_ratio && xy_ratio >= 0) || (x / y < xy_ratio && xy_ratio < 0))
		{
			my_mlx_pixel_put(img, start->x + x, start->y + y, 0x00FFFFFF);
			if (x > 0)
				x--;
			else if (x < 0)
				x++;	
		}
		else
		{
			my_mlx_pixel_put(img, start->x + x, start->y + y, 0x00FFFFFF);
			if (y > 0)
				y--;
			else if (y < 0)
				y++;
		}
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
