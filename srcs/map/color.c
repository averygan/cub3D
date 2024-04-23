/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:23:12 by yliew             #+#    #+#             */
/*   Updated: 2024/04/23 19:23:22 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	new_rgb(int *color)
{
	printf("R: %i, G: %i, B: %i\n", color[R], color[G], color[B]);
	return (color[R] << 16 | color[G] << 8 | color[B]);
}

int	*parse_colors(char *str)
{
	char	**arr;
	int		*rgb_arr;
	int		i;

	rgb_arr = malloc(sizeof(int));
	arr = ft_split(str, ',');
	i = 0;
	while (arr[i] && i < 3)
	{
		rgb_arr[i] = ft_atoi(arr[i]);
		i++;
	}
	// if (arr[i])
	//		print error
	return (rgb_arr);
}

/* temp values for testing */
void	init_colors(t_map *map)
{
	map->f_color = parse_colors(map->textures[E_F]);
	map->floor = new_rgb(map->f_color);
	map->c_color = parse_colors(map->textures[E_C]);
	map->ceiling = new_rgb(map->c_color);
	printf("floor: %u\nceiling: %u\n", map->floor, map->ceiling);
}
