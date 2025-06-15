/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anon <anon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:59:53 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/15 12:24:53 by anon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
// # ifdef __linux__
// #  include <mlx.h>
// # else
# include "../mlx/mlx.h"
// # endif
# include <stdlib.h> // malloc, free
# include <stdio.h>
# include <fcntl.h> // open
# include <unistd.h> // read, close
# include <stdbool.h>
# include <math.h>
#include <sys/time.h> // for gettimeofday

# ifndef DEBUG
#  define DEBUG 0
# endif

// statuses
# define E 0

// window dimensions
# define W_W 1024
# define W_H 768
# define NUM_TEX 4

typedef t_array_list	t_al;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	int		hex;
	char	*hex_str;
}	t_rgb;

enum e_tex
{
	TEX_NO,
	TEX_SO,
	TEX_WE,
	TEX_EA
};

// # ifdef __linux__
// // Linux
enum e_keys
{
	KEY_W = 119,
	KEY_E = 101,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_RIGHT = 65363,
	KEY_ESCAPE = 65307
};
// # else
// // Mac
// enum e_keys
// {
// 	KEY_W = 13,
// 	KEY_E = 14,
// 	KEY_A = 0,
// 	KEY_S = 1,
// 	KEY_D = 2,
// 	KEY_ESCAPE = 53,
// 	KEY_ARROW_LEFT = 123,
// 	KEY_ARROW_RIGHT = 124,
// };
// # endif

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_al	*map;
	char	*no_ptr;
	char	*so_ptr;
	char	*we_ptr;
	char	*ea_ptr;
	t_rgb	*ceiling;
	t_rgb	*floor;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	double	pos_x;
	double	pos_y;
	char	start_dir;
	int		player_counter;

	/* offscreen render buffer */
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		line_len;
	int		endian;

	/* wall textures */
	void	*tex_img[NUM_TEX];
	char	*tex_data[NUM_TEX];
	int		tex_w[NUM_TEX];
	int		tex_h[NUM_TEX];

	/* camera & movement */
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;

	/* key states */
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;

	char	*em;
	int		status;
	bool	running;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		tex_num;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

typedef struct s_camera_config
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_camera_config;

// main.c
void	error_exit(char *msg, t_game *game);

// init.c
t_game	*init_game(char *file);
void	init_rendering(t_game *g);

// debug.c
void	debug(const char *f, ...);

// parser.c
void	parse_map(char *file, t_game *game);
void	add_line_to_map(t_game *g, char *l);
bool	find_player_start(t_game *g, char *l, int row);

// configuration_line_parser.c
bool	parse_texture_configuration(char *l, t_game *g);
bool	parse_configuration_line(char *l, t_game *g);
bool	parse_color_configuration(char *l, t_game *g);
bool	extract_rgb(t_game *g, t_pair *p, t_rgb *rgb);

// configuration_line_parser_utils.c
int		is_configuration_line(char *l);
void	set_em(t_game *g, char *m, int s);

// parser_color.c
bool	extract_rgb(t_game *g, t_pair *p, t_rgb *rgb);
bool	set_rgb(t_game *g, t_rgb *rgb, t_pair *p);
bool	parse_color_configuration(char *l, t_game *g);
bool	is_color_configuration(char *l);

// parser_helpersc
t_pair	*parse_configuration(char *l);
void	free_pair(t_pair *p);
void	ft_free_split(char **arr, const char *s, char c);

// parser_texture.c
bool	parse_texture_configuration(char *l, t_game *g);
bool	is_texture_configuration(char *l);

// parser_gc.c
void	exit_with_free(char	*map_str, char *msg, t_game *game);
void	cleanup_reading(char *line, char *temp);

// parser_validator.c
int		has_consecutive_newlines(char *map_str);

// map_validator.c
bool	is_map_valid(t_game *g);

// map_enclosure_check.c
bool	check_enclosure(t_game *g);

// map_validator_utils.c
bool	is_player(const char c);

// application_gc.c
void	*destroy_game(t_game *g);
void	free_color(t_rgb **color);

// file_validator.c
int		is_valid_extension(char *file);

void	put_pixel(t_game *g, int x, int y, int color);

// renderer.c
int		render_next_frame(void *param);
void	draw_floor_and_ceiling(t_game *g);
void	cast_single_ray(t_game *g, int x);
void	init_ray(t_game *g, int x, t_ray *r);
void	do_dda(t_game *g, t_ray *r);
void	compute_draw_parameters(t_game *g, t_ray *r);
void	init_camera(t_game *g);

// void compute_step_side(t_game *g, t_ray *r);
void	move_dir(t_game *g, double dx, double dy);
void	rotate_player(t_game *g, double angle);

// action_handler.c
int		handle_exit(void *param);
int		handle_keypress(int key, t_game *g);
int		handle_keyrelease(int key, t_game *g);

// move.c
void	move_dir(t_game *g, double dx, double dy);
void	rotate_player(t_game *g, double angle);

#endif
