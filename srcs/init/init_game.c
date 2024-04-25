/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:02:40 by agan              #+#    #+#             */
/*   Updated: 2024/04/25 15:02:41 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game, t_map *map)
{
	int x;
	int y;
	t_pos *player_pos;

	x = 0;
	player_pos = &(game->player.pos);
	while (map->map_arr[x])
	{
		y = 0;
		while (map->map_arr[x][y])
		{
			if (is_player(map->map_arr[x][y]) != -1)
			{
				player_pos->x = x;
				player_pos->y = y;
				game->player.starting_dir = is_player(map->map_arr[x][y]);
				break ;
			}
			y++;
		}
		x++;
	}
}

void	init_game(t_game *game, t_map *map)
{
	init_player(game, map);
}
