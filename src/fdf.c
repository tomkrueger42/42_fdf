/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/20 15:52:50 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>

int	main(__unused int argc, __unused char **argv)
{
	char	*input_str;
	int	length;
	int	width;
	int	fd;

	length = 0;
	input_str = NULL;
	fd = open("fdf.txt", O_RDONLY);
	while (input_str != NULL || length == 0)
	{
		input_str = get_next_line(fd);
		length++;
		//free(input_str);
	}
	width = ft_strlen(input_str);
	close(fd);
	int	**arr;
	arr = ft_calloc(sizeof(int *), length);
	if (arr == NULL)
		return (0);
	length = 0;
	fd = open("fdf.txt", O_RDONLY);
	while (input_str != NULL || length == 0)
	{
		input_str = get_next_line(fd);
		arr[length] = ft_getnbrs(input_str);
		length++;
	}
	return (0);
}
