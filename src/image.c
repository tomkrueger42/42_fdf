/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 22:30:50 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/11 17:31:51 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
# include <math.h>

#include <stdio.h>

#define ROTATION 1
#define WARP 70

void	draw_wireframe(t_fdf *fdf, t_list *map, t_data *img)
{
	t_px	*origin;
	t_px	*cur;
	t_px	*var;
	int		x_count;
	int		y_count;
	int		px_distance;
	t_list	*parser;
	int		cur_height;
	int		height;

	y_count = 0;
	parser = map;
	px_distance = ft_min(2, WIN_X, WIN_Y) / (fdf->width + fdf->length / ROTATION);
	height = parser->content[0];
	origin = set_px(fdf->length * px_distance / ROTATION, px_distance + height, convert_color(fdf, ft_abs(height)));

	// draw_line(img, set_px(500, 500, convert_color(fdf, ft_abs(10))), set_px(500, 700, convert_color(fdf, ft_abs(0))));

	while (y_count < fdf->length)
	{
		x_count = 0;
		cur_height = parser->content[0];
		cur = set_px(origin->x, origin->y - cur_height, convert_color(fdf, ft_abs(cur_height)));
		while (x_count < fdf->width)
		{
			if (y_count < fdf->length - 1)	// y-lines
			{
				height = parser->next->content[x_count];
				var = set_px(cur->x - (px_distance / ROTATION), cur->y + (px_distance * WARP / 100) + cur_height - height, convert_color(fdf, ft_abs(height)));
				draw_line(img, cur, var);
			}
			if (x_count < fdf->width - 1)	// x-lines
			{
				height = parser->content[x_count + 1];
				var = set_px(cur->x + px_distance, cur->y + (px_distance / ROTATION * WARP / 100) +cur_height - height, convert_color(fdf, ft_abs(height)));
				draw_line(img, cur, var);
			}
			x_count++;
			cur->x += px_distance;
			cur->y += (px_distance / ROTATION) * WARP / 100 + cur_height;
			cur_height = parser->content[x_count];
			cur->y += - cur_height;
			cur->color = convert_color(fdf, ft_abs(cur_height));
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
	if (y == 0)
		xy_ratio = x;
	else
		xy_ratio = x / y;
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(img, start->x + x, start->y + y, set_color(start, end, ft_abs(x), ft_abs(y)));
		if (y == 0 || (x / y >= xy_ratio && xy_ratio >= 0) || (x / y <= xy_ratio && xy_ratio <= 0))
		{
			if (x > 0)
				x--;
			else if (x < 0)
				x++;
		}
		else
		{
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
