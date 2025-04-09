/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:59:27 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/09 23:56:14 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(char *msg, t_game *game)
{
	if (game && game->map)
		free_map(game->map, game->map_height);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./cub3d <map_file.cub>\n", NULL);
	if (!is_valid_extension(argv[1]))
		error_exit("Invalid file extension. Please provide .cub file\n", NULL);
	ft_bzero(&game, sizeof(t_game));
	parse_map(argv[1], &game);
	return (0);
}
