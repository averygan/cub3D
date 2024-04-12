/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:51:32 by agan              #+#    #+#             */
/*   Updated: 2024/04/12 15:51:32 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int map_valid_syntax(char map_c)
{
	if (map_c != '1' && map_c != '0' && map_c != ' ' && map_c != '\n' \
		&& map_c != 'N' && map_c != 'S' && map_c != 'E' && map_c != 'W')
		return (-1);
	return (0);
}

int map_syntax_checker(char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map_valid_syntax(map[i][j]))
				return (printf("map contains invalid characters\n"), -1);
		}
	}
	return 0;
}

/* function to get height and length, dup map arr */
char **dup_map_arr()
{
	
}

int map_checker(t_map *map, char **map_arr)
{
	(void)map;
	map_syntax_checker(map_arr);
	return 0;
}
