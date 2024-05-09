/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:28:18 by yliew             #+#    #+#             */
/*   Updated: 2024/05/09 16:28:19 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to check if there are multiple new lines in map content */
int	map_nl_checker(char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && j < 6)
	{
		while (str[i] == c)
			i++;
		if (str[i])
			j++;
		while (str[i] && str[i] != c)
			i++;
	}
	while (str[i] == c)
		i++;
	if (ft_strnstr(&str[i], "\n\n", ft_strlen(&str[i])))
		return (-1);
	return (0);
}
