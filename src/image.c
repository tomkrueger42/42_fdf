/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 22:30:50 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/17 15:35:25 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
# include <math.h>

#include <stdio.h>

#define WARP 70

void	draw_wireframe(t_fdf *fdf, t_list *map)
{
	t_px	*origin;
	t_px	*cur;
	int		cur_height;
	int		y_count;

	y_count = 0;
	origin = set_px(fdf->length * fdf->px_dist / ROTATION,
					fdf->px_dist + map->content[0],
					convert_color(fdf, ft_abs(map->content[0])));
	while (y_count < fdf->length)
	{
		cur_height = map->content[0];
		cur = set_px(origin->x,
					origin->y - cur_height,
					convert_color(fdf, ft_abs(cur_height)));
		set_lines(fdf, map, cur, y_count);
		free(cur);
		origin->x -= (fdf->px_dist / ROTATION);
		origin->y += fdf->px_dist * WARP / 100;
		map = map->next;
		y_count++;
	}
	free(origin);
	origin = NULL;
	// system("leaks fdf");
}

void	set_lines(t_fdf *fdf, t_list *map, t_px *cur, int y_count)
{
	int		x_count;
	int		cur_height;

	cur_height = map->content[0];
	x_count = 0;
	while (x_count < fdf->width)
	{
		if (y_count < fdf->length - 1)	// y-lines
			y_line(fdf, cur, cur_height, map->next->content[x_count]);
		if (x_count < fdf->width - 1)	// x-lines
			x_line(fdf, cur, cur_height, map->content[x_count + 1]);
		x_count++;
		cur->x += fdf->px_dist;
		cur->y += (fdf->px_dist / ROTATION) * WARP / 100 + cur_height;
		cur_height = map->content[x_count];
		cur->y += - cur_height;
		cur->color = convert_color(fdf, ft_abs(cur_height));
	}
}

void	y_line(t_fdf *fdf, t_px *cur, int cur_height, int height)
{
	t_px	*tmp;

	tmp = set_px(cur->x - (fdf->px_dist / ROTATION),
			cur->y + (fdf->px_dist * WARP / 100) + cur_height - height,
			convert_color(fdf, ft_abs(height)));
	draw_line(&fdf->img, cur, tmp);
}

void	x_line(t_fdf *fdf, t_px *cur, int cur_height, int height)
{
	t_px	*tmp;

	tmp = set_px(cur->x + fdf->px_dist,
				cur->y + (fdf->px_dist / ROTATION * WARP / 100)
				+ cur_height - height,
				convert_color(fdf, ft_abs(height)));
	draw_line(&fdf->img, cur, tmp);
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
		xy_ratio = x / y; // -2
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(img, start->x + x, start->y + y,
							set_color(start, end, ft_abs(x), ft_abs(y)));
		if (x > 0 && (y == 0 || (x / y >= xy_ratio && xy_ratio > 0) /* || (x / y < xy_ratio && xy_ratio < 0) */))
			x--;
		else if (x < 0 && (y == 0 || (x / y <= xy_ratio && xy_ratio < 0) /* || (x / y > xy_ratio && xy_ratio > 0) */))
			x++;
		else if (y > 0)
			y--;
		else if (y < 0)
			y++;
	}
	free(end);
	end = NULL;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
