/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:45:46 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/09 23:53:21 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	exit_with_free(char	*map_str, char *msg, t_game *game)
{
	free(map_str);
	error_exit(msg, game);
}

void	cleanup_reading(char *line, char *temp)
{
	free(temp);
	free(line);
	cleanup();
}
