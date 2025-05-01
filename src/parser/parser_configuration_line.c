/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_line_parser.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:25:51 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/01 18:37:21 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	parse_texture_configuration(char *l, t_game *g)
{
	t_pair	*p;

	p = parse_configuration(l);
	if (!p)
	{
		set_error_message(g, "Failed parse configuration\n", E);
		return (false);
	}
	if (ft_strncmp(p->first, "NO", 2) == 0)
		g->no_ptr = ft_strdup(p->second);
	else if (ft_strncmp(p->first, "SO", 2) == 0)
		g->so_ptr = ft_strdup(p->second);
	else if (ft_strncmp(p->first, "WE", 2) == 0)
		g->we_ptr = ft_strdup(p->second);
	else if (ft_strncmp(p->first, "EA", 2) == 0)
		g->ea_ptr = ft_strdup(p->second);
	else
	{
		set_error_message(g, "Unknown configuration identifier\n", E);
		return (false);
	}
	free_pair(p);
	return (true);
}

bool	extract_rgb(t_game *g, t_pair *p, t_rgb *rgb)
{
	char	**colors;

	colors = ft_split(p->second, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		set_error_message(g, "Incorrect colors\n", E);
		return (false);
	}
	rgb->r = ft_atoi(colors[0]);
	rgb->g = ft_atoi(colors[1]);
	rgb->b = ft_atoi(colors[2]);
	rgb->hex = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	rgb->hex_str = ft_strjoin("0x", itox(rgb->hex));
	return (true);
}

bool	set_rgb(t_game *g, t_rgb *rgb, t_pair *p)
{
	if (ft_strcmp(p->first, "F") == 0)
		g->floor = rgb;
	else if (ft_strcmp(p->first, "C") == 0)
		g->ceiling = rgb;
	else
	{
		set_error_message(g, "Unknown configuration identifier\n", E);
		return (free_pair(p), free(rgb), false);
	}
	return (true);
}

bool	parse_color_configuration(char *l, t_game *g)
{
	t_pair	*p;
	t_rgb	*rgb;

	// todo: move this initialization into init.c
	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
	{
		set_error_message(g, "Failed parse configuration\n", E);
		return (false);
	}
	p = parse_configuration(l);
	if (!p)
	{
		set_error_message(g, "Failed parse configuration\n", E);
		return (free(rgb), false);
	}
	if (!extract_rgb(g, p, rgb))
		return (free_pair(p), false);
	if (!set_rgb(g, rgb, p))
		return (false);
	free_pair(p);
	return (true);
}

/**
 * @brief Parses a control line and updates the game state accordingly.
 *
 * This function takes a trimmed string representing a control line and extracts
 * relevant information to update various fields in the provided game structure.
 * Control line consists of identifier followed by specific data:
 * - Texture identifiers (NO, SO, WE, EA) followed by a path to the texture file
 * - Color identifiers (F, C) followed by a string with the color in RGB format
 *   (e.g., "100,100,100")
 *
 * @param l A pointer to the trimmed string containing the control line to parse.
 * @param g A pointer to the t_game structure where parsed information will be
 * stored.
 *
 * @note The function modifies fields in the game structure based on the content
 * of @p l.
 */
bool	parse_configuration_line(char *l, t_game *g)
{
	if (is_texture_configuration(l))
		return (parse_texture_configuration(l, g));
	if (is_color_configuration(l))
		return (parse_color_configuration(l, g));
	return (false);
}
