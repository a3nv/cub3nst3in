/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_file_parser.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:49:26 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/14 22:27:21 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * By the time we're getting to parsing the map we should have all the config 
 * commands parsed otherwise such a map is invalid
 */
bool	config_parsed(t_game *g)
{
	return (g->floor != NULL && g->ceiling != NULL && g->so_ptr != NULL
		&& g->no_ptr != NULL && g->ea_ptr != NULL && g->we_ptr != NULL);
}

bool	parse_map_line(char *l, t_game *g)
{
	int		row;
	char	*t;

	t = ft_strtrim(l, " \t");
	if (g->map == NULL && (ft_strlen(t) == 0 || *t == '\n'))
		return (free(t), true);
	if (g->map != NULL && (ft_strlen(t) == 0 || *t == '\n'))
	{
		set_em(g, "Error: an empty line within the map\n", E);
		return (free(t), true);
	}
	if (!config_parsed(g))
	{
		set_em(g, "Error: missing configuration\n", E);
		return (free(t), false);
	}
	if (g->map == NULL)
		g->map = array_list_create(1);
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
		if (g->map != NULL)
		{
			set_em(g, "Error: unexpected data after map\n", E);
			return (false);
		}
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
	if (!l)
	{
		set_em(g, "Error: empty file\n", E);
		free(l);
		cleanup();
		return ;
	}
	while (l && g->status != E)
	{
		if (!process_line(l, g))
			break ;
		free(l);
		l = get_next_line(fd);
	}
	free(l);
	cleanup();
}

void	parse_map(char *file, t_game *g)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file\n", g);
	read_map_lines(fd, g);
	close(fd);
}
