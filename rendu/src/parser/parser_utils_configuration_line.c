/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_configuration_line.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:34:49 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/03 19:24:54 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_configuration_line(char *l)
{
	return (is_texture_configuration(l) || is_color_configuration(l));
}

void	set_em(t_game *g, char *m, int s)
{
	g->em = ft_strdup(m);
	g->status = s;
}
