/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:28:44 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/03 22:28:46 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_exit(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	destroy_game(g);
	return (0);
}

int	handle_keypress(int key, t_game *g)
{
	if (key == KEY_W)
		g->key_w = 1;
	else if (key == KEY_S)
		g->key_s = 1;
	else if (key == KEY_A)
		g->key_a = 1;
	else if (key == KEY_D)
		g->key_d = 1;
	else if (key == KEY_ARROW_LEFT)
		g->key_left = 1;
	else if (key == KEY_ARROW_RIGHT)
		g->key_right = 1;
	else if (key == KEY_ESCAPE)
		handle_exit(g);
	return (0);
}

int	handle_keyrelease(int key, t_game *g)
{
	if (key == KEY_W)
		g->key_w = 0;
	else if (key == KEY_S)
		g->key_s = 0;
	else if (key == KEY_A)
		g->key_a = 0;
	else if (key == KEY_D)
		g->key_d = 0;
	else if (key == KEY_ARROW_LEFT)
		g->key_left = 0;
	else if (key == KEY_ARROW_RIGHT)
		g->key_right = 0;
	return (0);
}
