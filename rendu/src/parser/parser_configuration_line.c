/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_configuration_line.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:25:51 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/02 21:55:49 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
