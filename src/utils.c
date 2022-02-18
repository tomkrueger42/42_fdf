/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:07:50 by tomkrueger        #+#    #+#             */
/*   Updated: 2022/02/18 12:41:03 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


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


void	del_content(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_stuff(t_fdf *fdf, t_list *map)
{
	// ft_lstclear(&map, &del_content);
	while (map != NULL)
	{
		free(map->content);
		map->content = NULL;
		map = map->next;
	}
	free(fdf);
	fdf = NULL;
}
