/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:28:06 by tomkrueger        #+#    #+#             */
/*   Updated: 2022/02/20 19:57:46 by tomkrueger       ###   ########.fr       */
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

int	convert_color(t_fdf *fdf, int height)
{
	double	percentage;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	percentage = (double)ft_abs(height) / (double)MHGHT;
	r = get_r(STD_COLOR) - (double)get_r(STD_COLOR ^ MAX_COLOR) * percentage;
	g = get_g(STD_COLOR) - (double)get_g(STD_COLOR ^ MAX_COLOR) * percentage;
	b = get_b(STD_COLOR) - (double)get_b(STD_COLOR ^ MAX_COLOR) * percentage;
	return (*(int *)(unsigned char [4]){b, g, r});
}

int	set_color(t_px *start, t_px *end, size_t x_counter, size_t y_counter)
{
	double	x;
	double	y;
	double	r;
	double	g;
	double	b;

	x = ft_abs(end->x - start->x);
	y = ft_abs(end->y - start->y);
	r = get_r(end->color) - get_r(start->color);
	g = get_g(end->color) - get_g(start->color);
	b = get_b(end->color) - get_b(start->color);
	r = r / (x + y) * (double)(x_counter + y_counter);
	g = g / (x + y) * (double)(x_counter + y_counter);
	b = b / (x + y) * (double)(x_counter + y_counter);

	return (*(int *)(unsigned char [4]){get_b(start->color) + (int)b,
			get_g(start->color) + (int)g, get_r(start->color) + (int)r});
}
