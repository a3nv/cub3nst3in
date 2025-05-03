/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_configuration_line.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:34:49 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/03 22:30:15 by iasonov          ###   ########.fr       */
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

void	set_error_message(t_game *g, char *m, int s)
{
	g->error_message = ft_strdup(m);
	g->status = s;
}

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
