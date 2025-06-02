/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser_texture.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iasonov <iasonov@student.42prague.com>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/12 00:00:00 by iasonov		   #+#	#+#			 */
/*   Updated: 2025/06/02 21:43:04 by iasonov		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
  parse_texture_configuration:
  – Expects a line like “NO path/to/north_texture.xpm”
  – Calls parse_configuration() → (“NO”, “path/to/…”)
  – Stores the strdup’d path into the correct t_game field.
*/
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
		free_pair(p);
		return (false);
	}
	free_pair(p);
	return (true);
}

/**
 * @brief Parses a control line and updates the game state accordingly.
 *
 * Returns true if the line starts with one of “NO ”, “SO ”, “WE ”, “EA ”
 * Used by parser_configuration_line.c to decide which parser‐routine to call.
 *
 * @param l A pointer to the trimmed string containing the control line to parse.
 *
 * @note The function modifies fields in the game structure based on the content
 * of @p l.
 */
bool	is_texture_configuration(char *l)
{
	if (!l)
		return (false);
	if (ft_strncmp(l, "NO ", 3) == 0)
		return (true);
	if (ft_strncmp(l, "SO ", 3) == 0)
		return (true);
	if (ft_strncmp(l, "WE ", 3) == 0)
		return (true);
	if (ft_strncmp(l, "EA ", 3) == 0)
		return (true);
	return (false);
}
