/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_gc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:43:49 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/03 19:40:15 by iasonov          ###   ########.fr       */
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

/*
** Frees the four texture‐path strings (no_ptr, so_ptr, we_ptr, ea_ptr).
*/
void	free_texture_paths(t_game *g)
{
	if (g->no_ptr)
	{
		free(g->no_ptr);
		g->no_ptr = NULL;
	}
	if (g->so_ptr)
	{
		free(g->so_ptr);
		g->so_ptr = NULL;
	}
	if (g->we_ptr)
	{
		free(g->we_ptr);
		g->we_ptr = NULL;
	}
	if (g->ea_ptr)
	{
		free(g->ea_ptr);
		g->ea_ptr = NULL;
	}
}

/*
** Frees a single t_rgb (floor or ceiling), including its hex_str.
*/
void	free_color(t_rgb **color)
{
	if (*color)
	{
		if ((*color)->hex_str)
			free((*color)->hex_str);
		free(*color);
		*color = NULL;
	}
}

/*
** Destroys the MLX display and frees the mlx_ptr itself.
*/
void	free_mlx(t_game *g)
{
	if (g->mlx_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
		g->mlx_ptr = NULL;
	}
}

/*
** Destroys images, frees the map, texture paths, color structs,
** MLX display, error message, and finally the t_game itself.
*/
void	*destroy_game(t_game *g)
{
	int	i;

	if (!g)
		return (NULL);
	if (g->mlx_ptr && g->img_ptr)
		mlx_destroy_image(g->mlx_ptr, g->img_ptr);
	i = 0;
	while (i < NUM_TEX)
	{
		if (g->mlx_ptr && g->tex_img[i])
			mlx_destroy_image(g->mlx_ptr, g->tex_img[i]);
		i++;
	}
	free_map(g);
	free_texture_paths(g);
	free_color(&g->floor);
	free_color(&g->ceiling);
	free_mlx(g);
	free(g->em);
	free(g);
	return (NULL);
}
