/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:49:26 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/09 23:50:43 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	read_map_lines(int fd, char **map_str)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	while (line)
	{
		temp = *map_str;
		*map_str = ft_strjoin(*map_str, line);
		if (!*map_str)
		{
			cleanup_reading(line, temp);
			return ;
		}
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
}

int	parse_map(char *file, t_game *game)
{
	int		fd;
	char	*map_str;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file\n", NULL);
	map_str = ft_strdup("");
	if (!map_str)
		exit_with_free(map_str, "Failed to init map", game);
	read_map_lines(fd, &map_str);
	close(fd);
	if (!map_str || *map_str == '\0')
		exit_with_free(map_str, "Invalid map: empty map file\n", game);
	if (has_consecutive_newlines(map_str))
		exit_with_free(map_str, "Invalid map: has multiple newlines\n", game);
	game->map = ft_split(map_str, '\n');
	if (!game->map)
	{
		game->map_height = count_height(game);
		exit_with_free(map_str, "Failed to parse map", game);
	}
	free(map_str);
	set_map_dimensions(game);
	return (1);
}
