/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:43:52 by agan              #+#    #+#             */
/*   Updated: 2024/04/25 17:43:52 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_player_dir(t_player *player, char c)
{
	if (c == 'N')
		return (player->dir.x = 0, player->dir.y = -1,
			player->plane.x = 0.66, player->plane.y = 0, 1);
	else if (c == 'S')
		return (player->dir.x = 0, player->dir.y = 1,
			player->plane.x = -0.66, player->plane.y = 0, 1);
	else if (c == 'E')
		return (player->dir.x = 1, player->dir.y = 0,
			player->plane.x = 0, player->plane.y = 0.66, 1);
	else if (c == 'W')
		return (player->dir.x = -1, player->dir.y = 0,
			player->plane.x = 0, player->plane.y = -0.66, 1);
	return (0);
}

int	init_player_pos(t_map *map, t_player *player)
{
	int	row;
	int	col;

	row = 0;
	while (map->map_arr[row])
	{
		col = 0;
		while (map->map_arr[row][col])
		{
			if (set_player_dir(player, map->map_arr[row][col]))
			{
				player->pos.x = col;
				player->pos.y = row;
				map->player_count++;
			}
			col++;
		}
		row++;
	}
	if (map->player_count != 1)
		return (print_err(PLAYER_ERR), -1);
	return (0);
}
