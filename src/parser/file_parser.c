/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:49:26 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/13 00:10:25 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	process_line(char *l, t_game *g)
{
	char	*t;

	if (!l || l == NULL || *l == '\n')
		return ;
	if (is_configuration_line(l))
	{
		t = ft_strtrim(l, " \t\n");
		parse_configuration_line(t, g);
	}
	else
	{
		if (g->map == NULL)
			g->map = array_list_create(1); 
		array_list_add(g->map, l);
	}
}

void	read_map_lines(int fd, t_game *g)
{
	char	*l;

	l = get_next_line(fd);
	while (l)
	{
		process_line(l, g);
		free(l);
		l = get_next_line(fd);
	}
}

void	print_game(t_game *g)
{
	int	i;

	debug("Control so: %s\n", g->so_ptr);
	debug("Control no: %s\n", g->no_ptr);
	debug("Control we: %s\n", g->we_ptr);
	debug("Control ea: %s\n", g->ea_ptr);
	debug("Control f: %s\n", g->floor->hex_str);
	debug("Control c: %s\n", g->ceiling->hex_str);

	i = 0;
	while (g->map->data[i])
	{
		debug("Line %d: %s", i, g->map->data[i]);
		i++;
	}
}

void	parse_map(char *file, t_game *g)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file\n", NULL);
	read_map_lines(fd, g);
	print_game(g);
	close(fd);
}
