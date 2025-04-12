/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_line_parser_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:34:49 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/13 00:21:38 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_texture_configuration(char *l)
{
	return ((l[0] == 'N' && l[1] == 'O')
		|| (l[0] == 'S' && l[1] == 'O')
		|| (l[0] == 'W' && l[1] == 'E')
		|| (l[0] == 'E' && l[1] == 'A'));
}

int	is_color_configuration(char *l)
{
	return ((l[0] == 'F' && l[1] == ' ')
		|| (l[0] == 'C' && l[1] == ' '));
}

int	is_configuration_line(char *l)
{
	return (is_texture_configuration(l) || is_color_configuration(l));
}
