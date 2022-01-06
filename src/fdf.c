/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:27:42 by tjensen           #+#    #+#             */
/*   Updated: 2022/01/06 23:22:14 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

// Tutorial:	https://harm-smits.github.io/42docs/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("keycode: %i\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int mouse_code, __unused t_vars *vars)
{
	if (mouse_code == 1)
		printf("left-click\n");
	if (mouse_code == 2)
		printf("right-click\n");
	if (mouse_code == 3)
		printf("middle-click\n");
	if (mouse_code == 4)
		printf("scroll-up\n");
	if (mouse_code == 5)
		printf("scroll-down\n");
	return (0);
}

int	main(void)
{
	struct s_vars	vars;
	struct s_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "fdf");
	
	img.img = mlx_new_image(vars.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int i = 0;
	while (i < 500)
	{
		int j = 0;
		while (j < 500)
		{
			my_mlx_pixel_put(&img, i, j, ((i / 2) << 16 | (j / 2)));
			j++;
		}
		i++;
	}
	
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
