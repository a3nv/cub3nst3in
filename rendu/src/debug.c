/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:55:57 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/13 00:19:22 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	debug(const char *f, ...)
{
	va_list	args;

	if (!DEBUG)
		return ;
	va_start(args, f);
	vprintf(f, args);
	va_end(args);
}
