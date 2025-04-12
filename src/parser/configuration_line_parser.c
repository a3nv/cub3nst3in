/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_line_parser.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:25:51 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/12 20:10:32 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>

/**
 * @brief Parses the part of the configuration line with identifier and command 
 * a path to the texture file
 *
 * @param trimmed configuration linem it is not gurantted that in between of an
 * identifier and path there will be a single space
 * @return a t_pair where first - is a key (identifier), second - a path to the
 * file. Path is trimmed of spaces, new line symbol and tabs.
 */
t_pair	*parse_configuration(char *l)
{
	char	*sep_ptr;
	long	key_size;
	char	*k;
	char	*v;

	sep_ptr = ft_strchr(l, ' ');
	if (!sep_ptr)
		return (NULL);
	key_size = sep_ptr - l;
	k = ft_strndup(l, key_size);
	v = ft_strtrim(ft_strdup(sep_ptr + 1), " \t\n");
	return (create_pair(k, v));
}

void	parse_texture_configuration(char *l, t_game *g)
{
	t_pair	*p;

	p = parse_configuration(l);
	if(ft_strncmp(p->first, "NO", 2) == 0)
		g->no_ptr = ft_strdup(p->second);
	else if(ft_strncmp(p->first, "SO", 2) == 0)
		g->so_ptr = ft_strdup(p->second);
	else if(ft_strncmp(p->first, "WE", 2) == 0)
		g->we_ptr = ft_strdup(p->second);
	else if(ft_strncmp(p->first, "EA", 2) == 0)
		g->ea_ptr = ft_strdup(p->second);
	else
		error_exit("Unknown configuration\n", g);
	free_pair(p);
}

void	parse_color_configuration(char *l, t_game *g)
{
	char	**colors;
	t_pair *p;	
	t_rgb	*rgb;

	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		error_exit("Failed parse configuration\n", g);
	p = parse_configuration(l);
	colors = ft_split(p->second, ',');
	rgb->r = ft_atoi(colors[0]);
	rgb->g = ft_atoi(colors[1]);
	rgb->b = ft_atoi(colors[2]);
	rgb->hex = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	rgb->hex_str = ft_strjoin("0x", itox(rgb->hex));
	if (ft_strcmp(p->first, "F") == 0)
		g->floor = rgb;
	else if (ft_strcmp(p->first, "C") == 0)
		g->ceiling = rgb;
	else 
		error_exit("Unknown configuration\n", g);
}

/**
 * @brief Parses a control line and updates the game state accordingly.
 *
 * This function takes a trimmed string representing a control line and extracts
 * relevant information to update various fields in the provided game structure.
 * Control line consists of identifier followed by specific data:
 * - Texture identifiers (NO, SO, WE, EA) followed by a path to the texture file
 * - Color identifiers (F, C) followed by a string with the color in RGB format (e.g., "100,100,100")
 *
 * @param l A pointer to the trimmed string containing the control line to parse.
 * @param g A pointer to the t_game structure where parsed information will be stored.
 *
 * @note The function modifies fields in the game structure based on the content of @p l.
 */
void	parse_configuration_line(char *l, t_game *g)
{

	if(is_texture_configuration(l))
		parse_texture_configuration(l, g);
	else if (is_color_configuration(l))
		parse_color_configuration(l, g);	
}
