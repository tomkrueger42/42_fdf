/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 22:30:50 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/10 01:45:05 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
# include <math.h>

#include <stdio.h>

#define ROTATION 2
#define WARP 70

void	draw_wireframe(t_fdf *fdf, t_list *map, t_data *img)
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
	px_distance = ft_min(2, WIN_X, WIN_Y) / (fdf->width + fdf->length / ROTATION);
	fdf->amplitude = px_distance / fdf->max_amp;
	if (fdf->amplitude < 1)
		fdf->amplitude = 1;
	height = parser->content[0] * fdf->amplitude;
	origin = set_px(fdf->length * px_distance / ROTATION, px_distance + height, 0x00FFFFFF /* - (height * 10) */);

	draw_line(img, set_px(500, 700, convert_color(fdf, 0)), set_px(700, 500, convert_color(fdf, 8)));
	
	// while (y_count < fdf->length)
	// {
	// 	x_count = 0;
	// 	height = parser->content[0] * fdf->amplitude;
	// 	cur = set_px(origin->x, origin->y - height, 0x00FFFFFF /* - (height * 10) */);
	// 	while (x_count < fdf->width - 1)
	// 	{
	// 		// y-lines
	// 		if (y_count < fdf->length - 1)
	// 		{
	// 			height = (parser->content[x_count] - parser->next->content[x_count]) * fdf->amplitude;
	// 			draw_line(img, cur, set_px(cur->x - (px_distance / ROTATION), cur->y + (px_distance * WARP / 100) + height, 0x00FFFFFF /* 0x00FFFFFF */ /* - (height * 10) */));
	// 		}
	//		// x-lines
	// 		height = (parser->content[x_count] - parser->content[x_count + 1]) * fdf->amplitude;
	// 		draw_line(img, cur, set_px(cur->x + px_distance, cur->y + (px_distance / ROTATION * WARP / 100) + height, 0x00FFFFFF /* - (height * 10) */));
	// 		cur->x += px_distance;
	// 		cur->y += (px_distance / ROTATION) * WARP / 100 + height;
	// 		x_count++;
	// 	}
	// 	// last y-line
	// 	if (y_count < fdf->length - 1)
	// 	{
	// 		height = (parser->content[x_count] - parser->next->content[x_count]) * fdf->amplitude;
	// 		draw_line(img, cur, set_px(cur->x - (px_distance / ROTATION), cur->y + px_distance * WARP / 100 + height, 0x00FFFFFF /* - (height * 10) */));
	// 	}
	// 	origin->x -= (px_distance / ROTATION);
	// 	origin->y += px_distance * WARP / 100;
	// 	parser = parser->next;
	// 	y_count++;
	// }
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
	int		color;

	x = end->x - start->x;
	y = end->y - start->y;
	printf("start color: %i | end color: %i\n", start->color, end->color);
	// 
	// still working on Farbverlauf between start and end pixel!!!
	// 
	color = (end->color - start->color) / (x + y);
	if (y == 0)
		y = 1;
	xy_ratio = x / y;
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(img, start->x + x, start->y + y, start->color - (color * (x + y)));
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
