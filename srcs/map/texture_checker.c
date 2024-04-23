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

/* returns a pointer to start of path after whitespace */
char *texture_whitespace(char *texture)
{
	int i;
	char *ret;

	i = 0;
	ret = NULL;
	while (texture[i] == ' ' || (texture[i] >= 8 && texture[i] <= 13))
		i++;
	if (texture[i])
		ret = ft_strdup(&texture[i]);
	return (ret);
}

/* gets a malloc'ed string of path */
int texture_parser(t_map *map, char **split_map)
{
	int i;
	
	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		if (!ft_strncmp("NO ", split_map[i], 3))
			map->textures[E_NO] = texture_whitespace(split_map[i]);
		else if (!ft_strncmp("SO ", split_map[i], 3))
			map->textures[E_SO] = texture_whitespace(split_map[i]);
		else if (!ft_strncmp("EA ", split_map[i], 3))
			map->textures[E_EA] = texture_whitespace(split_map[i]);
		else if (!ft_strncmp("WE ", split_map[i], 3))
			map->textures[E_WE] = texture_whitespace(split_map[i]);
		else if (!ft_strncmp("F ", split_map[i], 2))
			map->textures[E_F] = texture_whitespace(split_map[i] + 2);
		else if (!ft_strncmp("C ", split_map[i], 2))
			map->textures[E_C] = texture_whitespace(split_map[i] + 2);
	}
	if (!map->textures[E_NO] || !map->textures[E_SO] || !map->textures[E_EA] || !map->textures[E_WE] \
		|| !map->textures[E_F] || !map->textures[E_C])
		return (printf("error: invalid texture path\n"), -1);
	// printf("printing textures arr\n-----------------------\n");
	// print_arr(map->textures);
	return 0;
}

/* Checks first six lines 
- error if formatting does not match no, so, ea, we, f, c
- checks if count of each texture is 1 */
int texture_checker(t_game *game, char **split_map)
{
	int i;

	i = -1;
	t_map *map;
	map = &(game->map);
	while (++i < TEXTURE_COUNT)
	{
		if (!ft_strncmp("NO ", split_map[i], 3))
			map->valid_no++;
		else if (!ft_strncmp("SO ", split_map[i], 3))
			map->valid_so++;
		else if (!ft_strncmp("EA ", split_map[i], 3))
			map->valid_ea++;
		else if (!ft_strncmp("WE ", split_map[i], 3))
			map->valid_we++;
		else if (!ft_strncmp("F ", split_map[i], 2))
			map->valid_f++;
		else if (!ft_strncmp("C ", split_map[i], 2))
			map->valid_c++;
		else
			return (printf("error: invalid element in map\n"), -1);
	}
	if (map->valid_no == 1 && map->valid_so == 1 && map->valid_ea == 1 && map->valid_we == 1 \
		&& map->valid_f == 1 && map->valid_c == 1)
		texture_parser(&game->map, split_map);
	else
	{
		printf("%i %i %i %i %i %i", map->valid_no, map->valid_so, map->valid_ea, map->valid_we, map->valid_f, map->valid_c);
		printf("error: map does not have all required elements\n");
	}
	return 0;
}