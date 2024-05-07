/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:06:36 by agan              #+#    #+#             */
/*   Updated: 2024/05/06 13:06:36 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to rotate dir and plane left */
void	rotate_left(t_game *game, t_player *player)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dir.x;
	old_planex = player->plane.x;
	player->dir.x = player->dir.x * cos(-ROTSPEED)
		- player->dir.y * sin(-ROTSPEED);
	player->dir.y = old_dirx * sin(-ROTSPEED)
		+ player->dir.y * cos(-ROTSPEED);
	player->plane.x = player->plane.x * cos(-ROTSPEED)
		- player->plane.y * sin(-ROTSPEED);
	player->plane.y = old_planex * sin(-ROTSPEED)
		+ player->plane.y * cos(-ROTSPEED);
	render_frame(game, &game->player);
}

/* function to rotate dir and plane right */
void	rotate_right(t_game *game, t_player *player)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dir.x;
	old_planex = player->plane.x;
	player->dir.x = player->dir.x * cos(ROTSPEED)
		- player->dir.y * sin(ROTSPEED);
	player->dir.y = old_dirx * sin(ROTSPEED)
		+ player->dir.y * cos(ROTSPEED);
	player->plane.x = player->plane.x * cos(ROTSPEED)
		- player->plane.y * sin(ROTSPEED);
	player->plane.y = old_planex * sin(ROTSPEED)
		+ player->plane.y * cos(ROTSPEED);
	render_frame(game, &game->player);
}

/* function to move forward and backwards
based on player pos and dir * movement speed */
void	movement(int keysym, t_game *game, t_player *player, char **map_arr)
{
	if (keysym == W_KEY || keysym == UP_KEY)
	{
		if (map_arr[(int)(player->pos.y)][(int)(player->pos.x +
			player->dir.x * MOVESPEED)] != '1')
			player->pos.x += player->dir.x * MOVESPEED;
		if (map_arr[(int)(player->pos.y + player->dir.y * MOVESPEED)]
			[(int)(player->pos.x)] != '1')
			player->pos.y += player->dir.y * MOVESPEED;
	}
	else if (keysym == S_KEY || keysym == DOWN_KEY)
	{
		if (map_arr[(int)(player->pos.y)]
			[(int)(player->pos.x - player->dir.x * MOVESPEED)] != '1')
			player->pos.x -= player->dir.x * MOVESPEED;
		if (map_arr[(int)(player->pos.y - player->dir.y * MOVESPEED)]
			[(int)(player->pos.x)] != '1')
			player->pos.y -= player->dir.y * MOVESPEED;
	}
	render_frame(game, &game->player);
}
