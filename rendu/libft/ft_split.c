/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 23:34:05 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/23 22:17:02 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_splits(const char *s, char c)
{
	int	count;

	count = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count + 1);
}

int	add_token(char **res, int idx, const char *start, const char *ptr)
{
	int		len;
	char	*token;

	len = ptr - start;
	if (len == 0)
	{
		res[idx] = NULL;
		return (1);
	}
	token = malloc(len + 1);
	if (!token)
		return (0);
	ft_strlcpy(token, start, len + 1);
	res[idx] = token;
	return (1);
}

void	free_res(char **res, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

char	**split_loop(const char *s, char c,
	char **res)
{
	int			idx;
	const char	*start;

	idx = 0;
	start = s;
	while (*s)
	{
		if (*s == c)
		{
			if (add_token(res, idx, start, s) == 0)
				return (free_res(res, idx), NULL);
			idx++;
			start = s + 1;
		}
		s++;
	}
	if (add_token(res, idx, start, s) == 0)
		return (free_res(res, idx), NULL);
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		count;
	char	**ok;

	if (s == NULL || *s == '\0')
		return (NULL);
	count = count_splits(s, c);
	res = malloc((count + 1) * sizeof(*res));
	if (res == NULL)
	{
		return (NULL);
	}
	ok = split_loop(s, c, res);
	if (ok == NULL)
		return (NULL);
	res[count] = NULL;
	return (res);
}
