/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anon <anon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:02:17 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/09 15:35:17 by anon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	number_len(long number)
{
	int	len;

	len = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		len++;
		number = -number;
	}
	while (number >= 1)
	{
		len++;
		number /= 10;
	}
	return (len);
}

void	reverse(char *b, int len)
{
	int		i;
	char	t;

	i = 0;
	while (i < len / 2)
	{
		t = b[i];
		b[i] = b[len - i -1];
		b[len - i - 1] = t;
		i++;
	}
}

void	transform(unsigned int n, char *b, int *i)
{
	int		rem;

	while (n != 0)
	{
		rem = n % 16;
		if (rem < 10)
			b[(*i)++] = rem + '0';
		else
			b[(*i)++] = rem - 10 + 'a';
		n = n / 16;
	}
	b[*i] = '\0';
}

char	*itox(unsigned int n)
{
	int		i;
	int		l;
	char	*b;

	l = number_len(n);
	b = malloc(sizeof(char) * (l + 1));
	if (!b)
		return (NULL);
	i = 0;
	if (n == 0)
	{
		free(b);
		return (ft_strdup("0"));
	}
	transform(n, b, &i);
	b[i] = '\0';
	reverse(b, i);
	return (b);
}
