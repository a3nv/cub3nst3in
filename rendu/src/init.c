/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:45:35 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/03 20:48:56 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_game *g)
{
	g->player_x = -1;
	g->player_y = -1;
	g->start_dir = '\0';
	g->pos_x = 0.0;
	g->pos_y = 0.0;
}

void	init_map(t_game *g)
{
	int	i;

	g->map = NULL;
	g->player_counter = 0;
	init_player(g);
	g->no_ptr = NULL;
	g->so_ptr = NULL;
	g->we_ptr = NULL;
	g->ea_ptr = NULL;
	g->floor = NULL;
	g->ceiling = NULL;
	g->img_ptr = NULL;
	g->img_data = NULL;
	i = 0;
	while (i < 4)
	{
		g->tex_img[i] = NULL;
		g->tex_data[i] = NULL;
		g->tex_w[i] = 0;
		g->tex_h[i] = 0;
		i++;
	}
}

void	init_movement(t_game *g)
{
	g->key_w = 0;
	g->key_s = 0;
	g->key_a = 0;
	g->key_d = 0;
	g->key_left = 0;
	g->key_right = 0;
	g->dir_x = 0.0;
	g->dir_y = 0.0;
	g->plane_x = 0.0;
	g->plane_y = 0.0;
	g->move_speed = 0.0;
	g->rot_speed = 0.0;
	g->running = true;
}

void	set_defaults(t_game *g)
{
	g->mlx_ptr = NULL;
	g->win_ptr = NULL;
	g->status = 1;
	g->em = NULL;
	init_map(g);
	init_movement(g);
}

t_game	*init_game(char *file)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		return (NULL);
	set_defaults(g);
	parse_map(file, g);
	if (is_map_valid(g))
	{
		g->mlx_ptr = mlx_init();
		if (!g->mlx_ptr)
			error_exit("Error: Failed to init MLX\n", g);
		init_rendering(g);
		g->win_ptr = mlx_new_window(g->mlx_ptr, W_W, W_H, "cub3d");
		if (!g->win_ptr)
			error_exit("Error: Failed to create window\n", g);
	}
	return (g);
}
