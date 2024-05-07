/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checker_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:33:05 by yliew             #+#    #+#             */
/*   Updated: 2024/05/07 16:33:07 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || (c >= 8 && c <= 13));
}

void	skip_texture_whitespace(char **split_map, int i, int *j)
{
	*j = 0;
	while (is_whitespace(split_map[i][*j]))
		(*j)++;
}

bool	all_elements_found(t_map *map)
{
	return (map->valid_no == 1 && map->valid_so == 1 && map->valid_ea == 1
		&& map->valid_we == 1 && map->valid_f == 1 && map->valid_c == 1);
}

bool	all_textures_found(t_map *map)
{
	return (map->textures[E_NO] && map->textures[E_SO]
		&& map->textures[E_EA] && map->textures[E_WE]
		&& map->textures[E_F] && map->textures[E_C]);
}
