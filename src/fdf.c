/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/19 20:47:07 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>

int	main(__unused int argc, __unused char **argv)
{
	char	*input_str;
	int	length;
	int	fd;

	length = 0;
	input_str = NULL;
	fd = open("fdf.txt", O_RDONLY);
	while (input_str != NULL || length == 0)
	{
		input_str = get_next_line(fd);
		length++;
		printf("%i:\t%s", length, input_str);
		//free(input_str);
	}
	return (0);
}
