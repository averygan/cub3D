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

#include "cub3d.h"

/* checks if there are invalid syntax in map */
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

/* check spaces in map - if spaces are within map, replace with wall */
void replace_map_spaces(char **map_arr)
{
	int i;
	int j;

	i = 0;
	while (map_arr[i])
	{
		j = 0;
		while (map_arr[i][j] == ' ')
			j++;
		while (map_arr[i][j])
		{
			if (map_arr[i][j] == ' ')
				map_arr[i][j] = 1;
			j++;
		}
		i++;
	}
}

void map_height_width(t_map *map, char **map_arr)
{
	int height;
	int width;

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
	printf("height is %i\nwidth is %i\n", map->map_height, map->map_width);
}

/* function to check if row contains all '1's, checker for first and last rows */
int row_checker(char **map_arr, int i)
{
	int j;

	j = 0;
	while (map_arr[i][j])
	{
		if (map_arr[i][j] != '1' && map_arr[i][j] != ' ')
			return (-1);
		j++;
	}
	return (0);
}

/* malloc number of pointers for height
iterate through map arr
	malloc length + 2
	start each string with tilde
	while start of string is space, replace with tilde
	strcpy content of map for each row 
	get strlen -> fill in rest of the row with tilde
*/
char **dup_tmp_map(t_map *map)
{
	char **dup_arr;
	int i;
	int j;
	int len;

	dup_arr = malloc(sizeof(char *) * (map->map_height + 1));
	i = 0;
	while (map->map_arr[i])
	{
		j = 0;
		dup_arr[i] = malloc(sizeof(char) * (map->map_width + 3));
		dup_arr[i][j] = '~';
		while (map->map_arr[i][j] == ' ')
		{
			dup_arr[i][j + 1] = '~';
			j++;
		}
		while (map->map_arr[i][j])
		{
			dup_arr[i][j + 1] = map->map_arr[i][j];
			j++;
		}
		dup_arr[i][j + 1] = '\0';
		len = ft_strlen(dup_arr[i]);
		while (len < map->map_width + 2)
		{
			dup_arr[i][len] = '~';
			len++;
		}
		dup_arr[i][map->map_width + 2] = '\0';
		i++;
	}
	dup_arr[i] = NULL;
	return (dup_arr);
}

/* DFS 
base case: out of bounds or not tilde 
if adjacent cell is zero, return true 
recursively run DFS on adjacent cells */
bool closed_recursive(t_map *map, char **tmp_map, int row, int col)
{
	if (row < 0 || col < 0 || row >= map->map_height || col >= map->map_width || tmp_map[row][col] != '~')
		return (false);

	tmp_map[row][col] = '*';
	if ((row > 0 && tmp_map[row - 1][col] == '0') ||
		(row < map->map_height - 1 && tmp_map[row + 1][col] == '0') ||
		(col > 0 && tmp_map[row][col - 1] == '0') ||
		(col < map->map_width - 1 && tmp_map[row][col + 1] == '0'))
		return (true);

	return (closed_recursive(map, tmp_map, row - 1, col) ||
			closed_recursive(map, tmp_map, row + 1, col) ||
			closed_recursive(map, tmp_map, row, col - 1) ||
			closed_recursive(map, tmp_map, row, col + 1));
}

/* iterates through tildes to run DFS */
bool closed_checker(t_map *map, char **tmp_map)
{
	int row;
	int col;

	row = 0;
	while (row < map->map_height)
	{
		col = 0;
		while (col < map->map_width)
		{
			if (tmp_map[row][col] == '~')
				if (closed_recursive(map, tmp_map, row, col))
				{
					printf("map is not closed at [%i][%i]\n", row, col);
					return (free_arr(tmp_map), false);
				}
			col++;
		}
		row++;
	}
	return (true);
}

/* runs syntax checker
duplicates map array from buffer and stores in map.map_arr */
int map_checker(t_map *map, char **map_arr)
{
	char **tmp_map;
	if (map_syntax_checker(map_arr))
		return (-1);
	map->map_arr = dup_map_arr(map_arr);
	if (map->map_arr)
	{
		map_height_width(map, map_arr);
		if (row_checker(map_arr, 0) || row_checker(map_arr, map->map_height - 1))
			return (-1);
		tmp_map = dup_tmp_map(map);
		print_arr(tmp_map);
		if (!closed_checker(map, tmp_map))
			return (-1);
		replace_map_spaces(map->map_arr);
	}
	// print_arr(map->map_arr);
	return 0;
}
