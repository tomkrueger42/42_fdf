/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:12:23 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/20 22:29:26 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../lib/libft/includes/libft.h"

/* window size */

# define WIN_X	2000
# define WIN_Y	1000

/* void color and maximum height */

# define STD_COLOR 0xFFFFFF
# define MAX_COLOR 0xFF8800
# define MHGHT 20

/* define the y-warp of the drawn map */

# define WARP 70

/* fixed defines */

# define ESC_KEY	53

/* struct definition */

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_fdf
{
	int		length;
	int		width;
	int		max_height;
	int		height_multiple;
	int		px_dist;
	int		win_x;
	int		win_y;
	t_vars	vars;
	t_data	img;
}	t_fdf;

typedef struct	s_px
{
	int				x;
	int				y;
	unsigned int	color;
}	t_px;

/* function prototypes */

/* fdf.c */

int		main(int argc, char **argv);

/* map.c */

t_list	*make_map(t_fdf *fdf, t_list **map, char *file);
void	tweak_map(t_fdf *fdf, t_list **map);
void	print_map(t_fdf *fdf, t_list *map);

/* image.c */

void	draw_wireframe(t_fdf *fdf, t_list *map);

/* colors.c */

int		convert_color(t_fdf *fdf, int height);
int		set_color(t_px *start, t_px *end, size_t x_counter, size_t y_counter);

/* utils.c */

t_px	*set_px(int x, int y, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, void	*mlx, void *win);

#endif
