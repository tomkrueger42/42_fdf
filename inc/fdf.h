/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:12:23 by tkruger           #+#    #+#             */
/*   Updated: 2022/01/21 19:55:40 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "../lib/libft/includes/libft.h"

# include <stdio.h>

int		main(int argc, char **argv);
void	*make_map(struct s_list *map, char *file);


#endif
