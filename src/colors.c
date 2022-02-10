/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:28:06 by tomkrueger        #+#    #+#             */
/*   Updated: 2022/02/10 01:40:16 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

unsigned char	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

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
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	printf("convert_colors()\n");
	percentage = (double)height / (double)fdf->max_amp;
	t = (double)get_t(CAMP) * percentage;
	r = (double)get_r(CAMP) * percentage;
	g = (double)get_g(CAMP) * percentage;
	b = (double)get_b(CAMP) * percentage;
	return (*(int *)(unsigned char [4]){b, g, r, t});
}
