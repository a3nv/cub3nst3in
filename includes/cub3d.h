/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:59:53 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/09 23:55:56 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdlib.h> // malloc, free
# include <stdio.h>
# include <fcntl.h> // open
# include <unistd.h> // read, close

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectible_count;
	int		move_count;
	int		player_count;
	int		exit_count;
	int		was_on_exit;

	// Image pointers for different game components
	void	*wall_img;
	void	*collectible_img;
	void	*player_img;
	void	*exit_img;
	void	*floor_img;
}	t_game;

// main.c
void	error_exit(char *msg, t_game *game);

// parser.c
int		parse_map(char *file, t_game *game);

// parser_gc.c
void	exit_with_free(char	*map_str, char *msg, t_game *game);
void	cleanup_reading(char *line, char *temp);

// parser_utils.c
int		count_height(t_game *game);
void	set_map_dimensions(t_game *game);

// parser_validator.c
int		has_consecutive_newlines(char *map_str);

// gc.c
void	free_map(char **map, int height);

// file_validator.c
int		is_valid_extension(char *file);

#endif
