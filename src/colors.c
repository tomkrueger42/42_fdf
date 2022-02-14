/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:28:06 by tomkrueger        #+#    #+#             */
/*   Updated: 2022/02/14 12:45:29 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

unsigned char	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

unsigned char	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

unsigned char	get_b(int trgb)
{
	return (trgb & 0xFF);
}

unsigned int	convert_color(t_fdf *fdf, int height)
{
	double	percentage;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	percentage = (double)height / (double)fdf->max_height;
	r = get_r(CBASE) - (double)get_r(CBASE ^ CMAMP) * percentage;
	g = get_g(CBASE) - (double)get_g(CBASE ^ CMAMP) * percentage;
	b = get_b(CBASE) - (double)get_b(CBASE ^ CMAMP) * percentage;
	return (*(int *)(unsigned char [3]){b, g, r});
}

int	set_color(t_px *start, t_px *end, size_t x_counter, size_t y_counter)
{
	int		x;
	int		y;
	double	d_r;
	double	d_g;
	double	d_b;

	x = ft_abs(end->x - start->x);
	y = ft_abs(end->y - start->y);
	d_r = (double)(get_r(end->color) - get_r(start->color)) / (double)(x + y) * (x_counter + y_counter);
	d_g = (double)(get_g(end->color) - get_g(start->color)) / (double)(x + y) * (x_counter + y_counter);
	d_b = (double)(get_b(end->color) - get_b(start->color)) / (double)(x + y) * (x_counter + y_counter);
	return (*(int *)(unsigned char [3]){get_b(start->color) + d_b, get_g(start->color) + d_g, get_r(start->color) + d_r});
}
