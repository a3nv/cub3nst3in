/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:49:40 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/13 00:25:55 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_map_line(const char *l)
{
	bool	has_map_char;

	has_map_char = false;
	while (*l)
	{
		if (*l == ' ' || *l == '\t')
			++l;
		else if (*l == '0' || *l == '1'
			|| *l == 'N' || *l == 'S'
			|| *l == 'E' || *l == 'W')
		{
			has_map_char = true;
			++l;
		}
		else if (*l == '\n' || *l == '\r')
			++l;
		else
			return (false);
	}
	return (has_map_char);
}