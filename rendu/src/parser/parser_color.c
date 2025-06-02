/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iasonov <iasonov@student.42prague.com>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/12 00:00:00 by iasonov		   #+#	#+#			 */
/*   Updated: 2025/06/02 21:52:32 by iasonov          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
  extract_rgb:
  – Splits the string “R,G,B” (found in p->second) into three components.
  – Converts them to ints, stores into rgb->r, rgb->g, rgb->b.
  – Computes the 0xRRGGBB hex code and also creates a leading “0x…” string.
  – On failure, sets an error in g and returns false.
*/
bool	extract_rgb(t_game *g, t_pair *p, t_rgb *rgb)
{
	char	**colors;
	char	*hex_digits;

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
	hex_digits = itox(rgb->hex);
	rgb->hex_str = ft_strjoin("0x", hex_digits);
	free(hex_digits);
	ft_free_split(colors);
	return (true);
}

/*
  set_rgb:
  – If the identifier is “F”, sets g->floor = rgb;
  – If the identifier is “C”, sets g->ceiling = rgb;
  – Otherwise, reports an unknown identifier and frees both p & rgb.
*/
bool	set_rgb(t_game *g, t_rgb *rgb, t_pair *p)
{
	if (ft_strcmp(p->first, "F") == 0)
		g->floor = rgb;
	else if (ft_strcmp(p->first, "C") == 0)
		g->ceiling = rgb;
	else
	{
		set_error_message(g, "Unknown configuration identifier\n", E);
		free_pair(p);
		free(rgb);
		return (false);
	}
	return (true);
}

/*
  parse_color_configuration:
  – Allocates a new t_rgb struct on the heap.
  – Calls parse_configuration(line) to get (“F”/“C”, “R,G,B”).
  – extract_rgb → fills in rgb fields.
  – set_rgb   → assigns rgb to either g->floor or g->ceiling.
  – On any failure, cleans up and returns false.
*/
bool	parse_color_configuration(char *l, t_game *g)
{
	t_pair	*p;
	t_rgb	*rgb;

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
		return (free_pair(p), free(rgb), false);
	if (!set_rgb(g, rgb, p))
		return (false);
	return (free_pair(p), true);
}

bool	is_color_configuration(char *l)
{
	if (!l)
		return (false);
	if (ft_strncmp(l, "F ", 2) == 0)
		return (true);
	if (ft_strncmp(l, "C ", 2) == 0)
		return (true);
	return (false);
}
