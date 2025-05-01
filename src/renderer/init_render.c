/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:23:58 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/01 22:24:00 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Load one XPM texture into g->tex_img[idx] and g->tex_data[idx]...
*/
void	init_texture(t_game *g, int idx, char *path)
{
	int		w;
	int		h;
	void	*img;
	char	*data;
	int		tmp;

	img = mlx_xpm_file_to_image(g->mlx_ptr, path, &w, &h);
	if (!img)
		error_exit("Error\nFailed to load texture\n", g);
	data = mlx_get_data_addr(img, &tmp, &tmp, &tmp);
	g->tex_img[idx] = img;
	g->tex_data[idx] = data;
	g->tex_w[idx] = w;
	g->tex_h[idx] = h;
}

/*
** Loop over the four walls: NO, SO, WE, EA
*/
void	load_textures(t_game *g)
{
	init_texture(g, TEX_NO, g->no_ptr);
	init_texture(g, TEX_SO, g->so_ptr);
	init_texture(g, TEX_WE, g->we_ptr);
	init_texture(g, TEX_EA, g->ea_ptr);
}

/*
** Create the off-screen buffer where we'll draw every frame
*/
void	init_render_buffer(t_game *g)
{
	g->img_ptr = mlx_new_image(g->mlx_ptr, W_W, W_H);
	if (!g->img_ptr)
		error_exit("Error\nFailed to create render buffer\n", g);
	g->img_data = mlx_get_data_addr(g->img_ptr, &g->bpp,
			&g->line_len, &g->endian);
}

/*
** Set dir_x/dir_y + plane_x/plane_y from the map's N/S/E/W,
** and give some sensible default speeds.
*/
void	init_camera(t_game *g)
{
	char	dir;

	dir = g->start_dir;
	if (dir == 'N')
	{
		g->dir_x = 0;
		g->dir_y = -1;
		g->plane_x = 0.66;
		g->plane_y = 0;
	}
	else if (dir == 'S')
	{
		g->dir_x = 0;
		g->dir_y = 1;
		g->plane_x = -0.66;
		g->plane_y = 0;
	}
	else if (dir == 'E')
	{
		g->dir_x = 1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		g->dir_x = -1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = -0.66;
	}
	g->move_speed = 0.05;
	g->rot_speed = 0.03;
}

/*
** Public entry: call these three in init_game()
*/
void	init_rendering(t_game *g)
{
	load_textures(g);
	init_render_buffer(g);
	init_camera(g);
}
