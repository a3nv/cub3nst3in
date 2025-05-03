/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:45:35 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/03 22:27:53 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

void	set_defaults(t_game *g)
{
	g->mlx_ptr = NULL;
	g->win_ptr = NULL;
	g->win_ptr = NULL;
	g->status = 1;
}

t_game	*init_game(char *file)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		return (NULL);
	set_defaults(g);
	parse_map(file, g);
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		error_exit("Error\nFailed to init MLX\n", g);
	g->win_ptr = mlx_new_window(g->mlx_ptr, W_W, W_H, "cub3d");
	if (!g->win_ptr)
		error_exit("Error\nFailed to create window\n", g);
	init_rendering(g);
	return (g);
}
