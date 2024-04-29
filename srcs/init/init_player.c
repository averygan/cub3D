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

void	init_player(t_game *game, t_map *map)
{
	int x;
	int y;
	t_pos *player_pos;

	y = 0;
	player_pos = &(game->player.pos);
	while (map->map_arr[y])
	{
		x = 0;
		while (map->map_arr[y][x])
		{
			if (is_player(map->map_arr[y][x]) != -1)
			{
				player_pos->x = x;
				player_pos->y = y;
				game->player.starting_dir = is_player(map->map_arr[y][x]);
				break ;
			}
			x++;
		}
		y++;
	}
}

/* init player direction variables */
void player_dir(t_player *player)
{
	if (player->starting_dir == N)
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else if (player->starting_dir == S)
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
	else if (player->starting_dir == E)
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	else if (player->starting_dir == W)
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else
	{
		player->dir.x = 0;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0;
	}
}