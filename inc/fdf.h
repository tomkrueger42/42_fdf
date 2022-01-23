/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:12:23 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/23 18:46:09 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../lib/libft/includes/libft.h"

# include <stdio.h>

/* modifiable */

# define WIN_X		960
# define WIN_Y		540

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

/* function prototypes */

/* fdf.c */

int		main(int argc, char **argv);
void	*make_map(struct s_list *map, char *file);
int		key_hook(int keycode, void	*mlx, void *win);

/* image.c */

t_data	draw_wireframe(t_list *map, t_data img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


#endif
