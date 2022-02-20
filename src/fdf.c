/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:22:15 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/20 16:58:51 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void set_fdf(t_fdf *fdf, t_list *map)
{
	size_t	i;
	t_list	*parser;

	parser = map;
	fdf->max_height = 1;
	while (parser != NULL)
	{
		i = 0;
		while (i < fdf->width)
		{
			if (fdf->max_height < ft_abs(parser->content[i]))
				fdf->max_height = ft_abs(parser->content[i]);
			i += 2;
		}
		parser = parser->next;
	}	
	fdf->px_dist = ft_min(2, WIN_X / (fdf->width / 2 + fdf->length),
						WIN_Y / (fdf->width / 2 + fdf->length * WARP / 100));
	if (fdf->px_dist < 2)
		fdf->px_dist = 2;
}

int	main(int argc, char **argv)
{
	t_list	*map;
	t_fdf	*fdf;
	t_vars	vars;

	map = NULL;
	if (argc != 2)
		return (ft_putstr_fd("./fdf <filename of properly formatted map>\n", 2));
	fdf = ft_calloc(1, sizeof(struct s_fdf));
	if (fdf == NULL)
		return (0);
	if (make_map(fdf, &map, argv[1]) == NULL)
		return (0);
	set_fdf(fdf, map);
	tweak_map(fdf, &map);
	// print_map(fdf, map);
	fdf->vars.mlx = mlx_init();
	fdf->vars.win = mlx_new_window(fdf->vars.mlx, WIN_X, WIN_Y, "fdf");
	fdf->img.img = mlx_new_image(fdf->vars.mlx, WIN_X * 2, WIN_Y * 2);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
									&fdf->img.line_length, &fdf->img.endian);
	draw_wireframe(fdf, map);
	mlx_put_image_to_window(fdf->vars.mlx, fdf->vars.win, fdf->img.img, 0, 0);
	mlx_key_hook(fdf->vars.win, key_hook, &fdf->vars);
	mlx_loop(fdf->vars.mlx);
	return (0);
}
