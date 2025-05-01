/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:59:27 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/29 22:28:54 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



void	error_exit(char *msg, t_game *game)
{
	if (game && game->map)
		array_list_free(game->map);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	*g;

	if (argc != 2)
		error_exit("Usage: ./cub3d <map_file.cub>\n", NULL);
	if (!is_valid_extension(argv[1]))
		error_exit("Invalid file extension. Please provide .cub file\n", NULL);
	g = init_game(argv[1]);
	if (g->status == E)
		error_exit(g->error_message, g);
	mlx_loop_hook(g->mlx_ptr, render_next_frame, g);
	mlx_loop(g->mlx_ptr);
	return (0);
}
