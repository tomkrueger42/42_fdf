/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:07:50 by tomkrueger        #+#    #+#             */
/*   Updated: 2022/02/21 01:58:35 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdlib.h> // for EXIT_SUCCESS portability

t_px	*set_px(int x, int y, int color)
{
	t_px	*new;

	new = malloc(sizeof(struct s_px) * 1);
	if (new == NULL)
		return (NULL);
	new->x = x;
	new->y = y;
	new->color = color;
	return (new);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, void	*mlx, void *win)
{

	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	return (0);
}
