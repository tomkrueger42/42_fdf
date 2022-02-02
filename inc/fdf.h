/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:12:23 by tkruger           #+#    #+#             */
/*   Updated: 2022/02/02 21:47:18 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../lib/libft/includes/libft.h"

# include <math.h>

# include <stdio.h>

/* mlx window and image */

# define WIDTH	4

# define WIN_X	960
# define WIN_Y	540
# define WIN_U	9
# define IMG_X	WIN_X / 10 * WIN_U
# define IMG_Y	WIN_Y / 10 * WIN_U

/* defines */

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

typedef struct	s_px
{
	int	x;
	int	y;
	int color;
}	t_px;

/* function prototypes */

/* fdf.c */

int		main(int argc, char **argv);
t_list	*make_map(t_list *map, char *file);
int		key_hook(int keycode, void	*mlx, void *win);

/* image.c */

void	draw_wireframe(t_list *map, t_data *img);
t_px	*set_px(int x, int y, int color);
void	draw_line(t_data *img, t_px *start, t_px *end);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


#endif
