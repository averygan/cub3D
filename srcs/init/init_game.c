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

int	init_game_struct(t_game *game)
{
	int	i;

	i = 0;
	while (i < WALL_COUNT)
	{
		game->walls[i].ptr = NULL;
		game->walls[i].colors = NULL;
		i++;
	}
	game->mlx_ptr = NULL;
	game->mlx_ptr = mlx_init();
	game->win_ptr = NULL;
	game->display.ptr = NULL;
	game->minimap.ptr = NULL;
	game->f_color = NULL;
	game->c_color = NULL;
	game->floor = 0;
	game->ceiling = 0;
	return (0);
}
