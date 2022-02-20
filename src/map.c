/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:36:25 by tomkrueger        #+#    #+#             */
/*   Updated: 2022/02/20 19:58:08 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <fcntl.h>

#include <stdio.h>

int	*extract_values(char **splitted);

t_list	*make_map(t_fdf *fdf, t_list **map, char *file)
{
	int		fd;
	char	*line;
	int		*nbrs;
	
	fd = open(file, O_RDONLY);
	line = NULL;
	fdf->width = -1;
	while (line != NULL || fdf->width == -1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (fdf->width == -1)
			fdf->width = (ft_count_nbrs(line) - ft_count_char(line, ',')) * 2;
		nbrs = extract_values(ft_split_free(ft_strtrim_free(line, "\n"), ' '));
		ft_lstadd_back(map, ft_lstnew(nbrs));
	}
	close(fd);
	fdf->length = ft_lstsize(*map);
	return (*map);
}

int	*extract_values(char **splitted)
{
	int		*nbrs;
	size_t	splitted_len;
	size_t	i;

	if (splitted == NULL)
		return (NULL);
	i = 0;
	splitted_len = ft_arrlen(splitted);
	nbrs = ft_calloc(splitted_len * 2, sizeof(*nbrs));
	if (nbrs == NULL)
		return (NULL);
	i = 0;
	while (i < splitted_len * 2)
	{
		nbrs[i] = ft_atoi(splitted[i / 2]);
		if (ft_strchr(splitted[++i / 2], ',') == NULL)
			nbrs[i] = -1;
		else
			nbrs[i] = ft_atoi_base(ft_strchr(splitted[i / 2], ',') + 3, 16);
		free(splitted[i / 2]);
		splitted[i++ / 2] = NULL;
	}
	free(splitted);
	splitted = NULL;
	return (nbrs);
}

void	tweak_map(t_fdf *fdf, t_list **map)
{
	t_list	*parser;
	size_t	i;

	parser = *map;
	while (parser != NULL)
	{
		i = 0;
		while (i < fdf->width && MHGHT != 0)
		{
			parser->content[i++] *= (double)MHGHT / (double)fdf->max_height;
			if (parser->content[i] == -1 && MAX_COLOR != 0x0)
				parser->content[i] = convert_color(fdf, parser->content[i - 1]);
			else if (parser->content[i] == -1)
				parser->content[i] = STD_COLOR;
			i++;
		}
		parser = parser->next;
	}
}

void	print_map(t_fdf *fdf, t_list *map)
{
	int	i;
	int	c = 0;

	if (map == NULL)
		return ;
	while (map != NULL)
	{
		i = 0;
		while (i < fdf->width)
		{
			printf(" %i,", map->content[i]);
			i++;
			printf("%x", map->content[i]);
			i++;
		}
		printf("\n");
		map = map->next;
	}
}
