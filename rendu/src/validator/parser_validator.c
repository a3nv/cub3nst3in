/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:50:15 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/09 23:54:49 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	has_consecutive_newlines(char *map_str)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isspace(map_str[i]))
		i++;
	j = ft_strlen(map_str);
	while (ft_isspace(map_str[j - 1]))
		j--;
	while (i < j)
	{
		if (ft_isspace(map_str[i]) && ft_isspace(map_str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}
