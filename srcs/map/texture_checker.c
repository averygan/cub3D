/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:16:22 by agan              #+#    #+#             */
/*   Updated: 2024/04/12 16:16:23 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || (c >= 8 && c <= 13));
}

/* returns a pointer to start of path after whitespace */
char *texture_whitespace(char *texture)
{
	int i;
	char *ret;

	i = 0;
	ret = NULL;
	while (is_whitespace(texture[i]))
		i++;
	if (texture[i])
		ret = ft_strdup(&texture[i]);
	return (ret);
}

/* gets a malloc'ed string of path */
int texture_parser(t_map *map, char **split_map)
{
	int i;
	int	j;
	
	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		j = 0;
		while (is_whitespace(split_map[i][j]))
			j++;
		if (!ft_strncmp("NO ", &split_map[i][j], 3))
			map->textures[E_NO] = texture_whitespace(&split_map[i][j + 2]);
		else if (!ft_strncmp("SO ", &split_map[i][j], 3))
			map->textures[E_SO] = texture_whitespace(&split_map[i][j + 2]);
		else if (!ft_strncmp("EA ", &split_map[i][j], 3))
			map->textures[E_EA] = texture_whitespace(&split_map[i][j + 2]);
		else if (!ft_strncmp("WE ", &split_map[i][j], 3))
			map->textures[E_WE] = texture_whitespace(&split_map[i][j + 2]);
		else if (!ft_strncmp("F ", &split_map[i][j], 2))
			map->textures[E_F] = texture_whitespace(&split_map[i][j + 1]);
		else if (!ft_strncmp("C ", &split_map[i][j], 2))
			map->textures[E_C] = texture_whitespace(&split_map[i][j + 1]);
	}
	if (!map->textures[E_NO] || !map->textures[E_SO] || !map->textures[E_EA] || !map->textures[E_WE] \
		|| !map->textures[E_F] || !map->textures[E_C])
		return (print_err(TEXTURE_PATH_ERR), -1);
	return (0);
}

/* Checks first six lines 
- error if formatting does not match no, so, ea, we, f, c
- checks if count of each texture is 1 */
int texture_checker(t_map *map, char **split_map)
{
	int i;
	int	j;

	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		j = 0;
		while (is_whitespace(split_map[i][j]))
			j++;
		if (!ft_strncmp("NO ", &split_map[i][j], 3))
			map->valid_no++;
		else if (!ft_strncmp("SO ", &split_map[i][j], 3))
			map->valid_so++;
		else if (!ft_strncmp("EA ", &split_map[i][j], 3))
			map->valid_ea++;
		else if (!ft_strncmp("WE ", &split_map[i][j], 3))
			map->valid_we++;
		else if (!ft_strncmp("F ", &split_map[i][j], 2))
			map->valid_f++;
		else if (!ft_strncmp("C ", &split_map[i][j], 2))
			map->valid_c++;
		else
			return (print_err(ELE_ERR), -1);
	}
	if (map->valid_no == 1 && map->valid_so == 1 && map->valid_ea == 1
		&& map->valid_we == 1 && map->valid_f == 1 && map->valid_c == 1)
		texture_parser(map, split_map);
	else
		return (print_err(ELE_COUNT_ERR), -1);
	return (0);
}
