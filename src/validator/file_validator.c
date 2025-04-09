/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:49:50 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/09 23:54:43 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (extension && ft_strncmp(extension, ".ber", 5) == 0)
		return (1);
	return (0);
}
