/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:07:50 by tomkrueger        #+#    #+#             */
/*   Updated: 2022/02/14 13:08:23 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
