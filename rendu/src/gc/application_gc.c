/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_gc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:43:49 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/29 21:40:18 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(t_game *g)
{
	if (g->map)
	{
		array_list_free(g->map);
		g->map = NULL;
	}
}

void	*destroy_game(t_game *g)
{
	int	i;

	if (!g)
		return (NULL);
	if (g->mlx_ptr && g->img_ptr)
		mlx_destroy_image(g->mlx_ptr, g->img_ptr);
	if (g->mlx_ptr && g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	i = 0;
	while (i < NUM_TEX)
	{
		if (g->mlx_ptr && g->tex_img[i])
			mlx_destroy_image(g->mlx_ptr, g->tex_img[i]);
		i++;
	}
	free_map(g);
	free(g->no_ptr);
	free(g->so_ptr);
	free(g->we_ptr);
	free(g->ea_ptr);
	free(g->ceiling);
	free(g->floor);
	free(g->error_message);
	free(g);
	return (NULL);
}
