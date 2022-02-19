/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:12:23 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/19 17:01:07 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../lib/libft/includes/libft.h"

/* window size */

# define WIN_X	1440
# define WIN_Y	780

/* void color and maximum height */

# define CVOID 0xFFFFFF
# define MHGHT 100

/* define the rotation and y-warp of the drawn map */

# define ROTATION 1
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
	int		px_dist;
	int		win_width;
	int		win_length;
	int		height_multiple;
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
t_list	*make_map(t_fdf *fdf, t_list *lst, char *file);
void 	set_fdf(t_fdf *fdf, t_list *map);
int		key_hook(int keycode, void	*mlx, void *win);

/* image.c */

void	draw_wireframe(t_fdf *fdf, t_list *map);
void	set_lines(t_fdf *fdf, t_list *map, t_px *cur, int y_count);
void	y_line(t_fdf *fdf, t_px *cur, int cur_height, int *height_color);
void	x_line(t_fdf *fdf, t_px *cur, int cur_height, int *height_color);
void	draw_line(t_data *img, t_px *start, t_px *end);

/* colors.c */

unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);
unsigned int	convert_color(t_fdf *fdf, int height);
int				set_color(t_px *start, t_px *end, size_t x_counter, size_t y_counter);

/* utils.c */

t_px	*set_px(int x, int y, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* cleanup.c */

void	del(void *ptr);
void	free_stuff(t_fdf *fdf, t_list *map);

#endif
