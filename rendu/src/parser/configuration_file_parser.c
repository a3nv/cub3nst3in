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
	array_list_add(g->map, l);
	row = g->map->size - 1;
	return (free(t), find_player_start(g, l, row));
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

void	print_game(t_game *g)
{
	int	i;

	debug("Control no: %s\n", g->no_ptr);
	debug("Control so: %s\n", g->so_ptr);
	debug("Control we: %s\n", g->we_ptr);
	debug("Control ea: %s\n", g->ea_ptr);
	if (g->floor)
		debug("Control f: %s\n", g->floor->hex_str);
	if (g->ceiling)
		debug("Control c: %s\n", g->ceiling->hex_str);
	i = 0;
	if (g->map)
	{
		while (g->map->data[i])
		{
			debug("Line %d: %s", i, g->map->data[i]);
			i++;
		}
	}
}

void	parse_map(char *file, t_game *g)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file\n", NULL);
	read_map_lines(fd, g);
	if (g->status != E)
		print_game(g);
	close(fd);
}
