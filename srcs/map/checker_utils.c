/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:57:34 by agan              #+#    #+#             */
/*   Updated: 2024/05/07 15:57:34 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* check spaces in map - if spaces are within map, replace with wall */
void	replace_map_spaces(char **map_arr)
{
	int	i;
	int	j;

	i = 0;
	while (map_arr[i])
	{
		j = 0;
		while (map_arr[i][j] == ' ')
			j++;
		while (map_arr[i][j])
		{
			if (map_arr[i][j] == ' ')
				map_arr[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	map_height_width(t_map *map, char **map_arr)
{
	int	height;
	int	width;

	height = 0;
	width = ft_strlen(map_arr[0]);
	while (map_arr[height])
	{
		if ((unsigned long)width < ft_strlen(map_arr[height]))
			width = ft_strlen(map_arr[height]);
		height++;
	}
	map->map_height = height;
	map->map_width = width;
}

/* function to replace spaces within map with tilde 
copies map content */
void	format_tmp_map(t_map *map, char **dup_arr, int *i, int *j)
{
	dup_arr[*i][*j] = '~';
	while (map->map_arr[*i][*j] == ' ')
	{
		dup_arr[*i][*j + 1] = '~';
		(*j)++;
	}
	while (map->map_arr[*i][*j])
	{
		dup_arr[*i][*j + 1] = map->map_arr[*i][*j];
		(*j)++;
	}
}

/* malloc number of pointers for height
iterate through map arr
	malloc length + 2
	start each string with tilde
	while start of string is space, replace with tilde
	strcpy content of map for each row 
	get strlen -> fill in rest of the row with tilde
*/
char	**dup_tmp_map(t_map *map)
{
	char	**dup_arr;
	int		i;
	int		j;
	int		len;

	dup_arr = malloc(sizeof(char *) * (map->map_height + 1));
	if (!dup_arr)
		return (NULL);
	i = -1;
	while (map->map_arr[++i])
	{
		j = 0;
		dup_arr[i] = malloc(sizeof(char) * (map->map_width + 3));
		format_tmp_map(map, dup_arr, &i, &j);
		dup_arr[i][j + 1] = '\0';
		len = ft_strlen(dup_arr[i]);
		while (len < map->map_width + 2)
		{
			dup_arr[i][len] = '~';
			len++;
		}
		dup_arr[i][map->map_width + 2] = '\0';
	}
	dup_arr[i] = NULL;
	return (dup_arr);
}
