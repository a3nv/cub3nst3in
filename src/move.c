#include "../includes/cub3d.h"

/*
** Move in direction (dx,dy), with simple AABB collision
*/
void move_dir(t_game *g, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = g->pos_x + dx;
	ny = g->pos_y;
	if (g->map->data[(int)ny][(int)nx] == '0')
		g->pos_x = nx;
	nx = g->pos_x;
	ny = g->pos_y + dy;
	if (g->map->data[(int)ny][(int)nx] == '0')
		g->pos_y = ny;
}

/*
** Rotate dir and plane by angle (radians)
*/
void rotate_player(t_game *g, double angle)
{
	double	old_dx;
	double	old_px;

	old_dx = g->dir_x;
	g->dir_x = g->dir_x * cos(angle) - g->dir_y * sin(angle);
	g->dir_y = old_dx * sin(angle) + g->dir_y * cos(angle);
	old_px = g->plane_x;
	g->plane_x = g->plane_x * cos(angle) - g->plane_y * sin(angle);
	g->plane_y = old_px * sin(angle) + g->plane_y * cos(angle);
}