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
int	map_syntax_checker(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map_valid_syntax(map[i][j]))
				return (print_err(MAP_SYNTAX_ERR), -1);
		}
	}
	return (0);
}

/* function to check if row contains all '1's, 
checker for first and last rows */
int	row_checker(char **map_arr, int i)
{
	int	j;

	j = 0;
	while (map_arr[i][j])
	{
		if (map_arr[i][j] != '1' && map_arr[i][j] != ' ')
			return (-1);
		j++;
	}
	return (0);
}

/* DFS 
base case: out of bounds or not tilde 
if adjacent cell is zero, return true 
recursively run DFS on adjacent cells */
bool	closed_recursive(t_map *map, char **tmp_map, int row, int col)
{
	if (row < 0 || col < 0 || row >= map->map_height || \
		col >= map->map_width || tmp_map[row][col] != '~')
		return (false);
	tmp_map[row][col] = '*';
	if ((row > 0 && tmp_map[row - 1][col] == '0') ||
		(row < map->map_height - 1 && tmp_map[row + 1][col] == '0') ||
		(col > 0 && tmp_map[row][col - 1] == '0') ||
		(col < map->map_width - 1 && tmp_map[row][col + 1] == '0'))
		return (true);
	return (closed_recursive(map, tmp_map, row - 1, col) || \
			closed_recursive(map, tmp_map, row + 1, col) || \
			closed_recursive(map, tmp_map, row, col - 1) || \
			closed_recursive(map, tmp_map, row, col + 1));
}

/* iterates through tildes to run DFS */
bool	closed_checker(t_map *map, char **tmp_map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->map_height)
	{
		col = 0;
		while (col < map->map_width)
		{
			if (tmp_map[row][col] == '~')
			{
				if (closed_recursive(map, tmp_map, row, col))
					return (print_map_not_closed(row, col), false);
			}
			col++;
		}
		row++;
	}
	return (true);
}

/* runs syntax checker
duplicates map array from buffer and stores in map.map_arr */
int	map_checker(t_map *map, char **map_arr)
{
	char	**tmp_map;

	if (map_syntax_checker(map_arr))
		return (-1);
	map->map_arr = dup_map_arr(map_arr);
	if (!map->map_arr)
		return (print_err(MEM_ERR), -1);
	if (map->map_arr)
	{
		map_height_width(map, map_arr);
		if (row_checker(map_arr, 0) || \
			row_checker(map_arr, map->map_height - 1))
			return (-1);
		tmp_map = dup_tmp_map(map);
		if (!tmp_map)
			return (print_err(MEM_ERR), -1);
		if (!closed_checker(map, tmp_map))
			return (free_arrays(tmp_map), -1);
		replace_map_spaces(map->map_arr);
		free_arrays(tmp_map);
	}
	return (0);
}
