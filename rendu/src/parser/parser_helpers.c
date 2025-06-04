/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser_helpers.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iasonov <iasonov@student.42prague.com>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/12 00:00:00 by iasonov		   #+#	#+#			 */
/*   Updated: 2025/06/02 21:44:10 by iasonov		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
  parse_configuration:
  – Splits an input line at the first space into (key, value) pair.
  – e.g. “NO ./path/to.xpm” → (“NO”, “./path/to.xpm”).
  – If either allocation fails, it returns NULL.
*/
t_pair	*parse_configuration(char *l)
{
	char	*sep_ptr;
	long	key_size;
	char	*k;
	char	*v;
	t_pair	*p;

	sep_ptr = ft_strchr(l, ' ');
	if (!sep_ptr)
		return (NULL);
	key_size = sep_ptr - l;
	k = ft_strndup(l, key_size);
	if (!k)
		return (NULL);
	v = ft_strtrim(sep_ptr + 1, " \t\n");
	if (!v)
		return (free(k), NULL);
	p = create_pair(k, v);
	return (free(k), free(v), p);
}

/*
  ft_free_split:
  – Iterates through a NULL-terminated char ** (as returned by ft_split)
  – Frees each string, then frees the array pointer itself.
  – Handy for cleaning up after extract_rgb() above.
*/
void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}
