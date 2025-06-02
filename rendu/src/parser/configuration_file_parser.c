/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_file_parser.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:49:26 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/03 22:31:26 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	parse_map_line(char *l, t_game *g)
{
	int		row;
	char	*t;

	if (g->map == NULL)
		g->map = array_list_create(1);
	t = ft_strtrim(l, " \t");
	if (ft_strlen(t) == 0 || *t == '\n')
		return (free(t), true);
	free(t);
	array_list_add(g->map, l);
	row = g->map->size - 1;
	return (find_player_start(g, l, row));
}

bool	process_line(char *l, t_game *g)
{
	char	*t;
	bool	r;

	if (!l || *l == '\0')
		return (false);
	if (is_configuration_line(l))
	{
		t = ft_strtrim(l, " \t\n");
		r = parse_configuration_line(t, g);
		return (free(t), r);
	}
	r = parse_map_line(l, g);
	return (r);
}

void	read_map_lines(int fd, t_game *g)
{
	char	*l;

	l = get_next_line(fd);
	while (l && g->status != E)
	{
		if (!process_line(l, g))
		{
			free(l);
			break ;
		}
		free(l);
		l = get_next_line(fd);
	}
}

void	parse_map(char *file, t_game *g)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file\n", NULL);
	read_map_lines(fd, g);
	close(fd);
}
