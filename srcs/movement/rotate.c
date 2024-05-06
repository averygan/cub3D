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

void rotate(t_game *game, t_player *player, int keysym)
{
	double old_dirx = player->dir.x; 
	double old_planex = player->plane.x;
	// rotate left
	if (keysym == A_KEY)
	{
		// printf("dirx is %f, diry is %f\n", player->dir.x, player->dir.y);
		player->dir.x = player->dir.x * cos(-ROTSPEED) - player->dir.y * sin(-ROTSPEED);
		player->dir.y = old_dirx * sin(-ROTSPEED) + player->dir.y * cos(-ROTSPEED);
		// printf("dirx is %f, diry is %f\n", player->dir.x, player->dir.y);
		player->plane.x = player->plane.x * cos(-ROTSPEED) - player->plane.y * sin(-ROTSPEED);
		player->plane.y = old_planex * sin(-ROTSPEED) + player->plane.y * cos(-ROTSPEED);
	}
	// rotate right
	else if (keysym == D_KEY)
	{
		// printf("dirx is %f, diry is %f\n", player->dir.x, player->dir.y);
		player->dir.x = player->dir.x * cos(ROTSPEED) - player->dir.y * sin(ROTSPEED);
		player->dir.y = old_dirx * sin(ROTSPEED) + player->dir.y * cos(ROTSPEED);
		// printf("dirx is %f, diry is %f\n", player->dir.x, player->dir.y);
		player->plane.x = player->plane.x * cos(ROTSPEED) - player->plane.y * sin(ROTSPEED);
		player->plane.y = old_planex * sin(ROTSPEED) + player->plane.y * cos(ROTSPEED);
	}
	render_frame(game, &game->player);
}

void movement(int keysym, t_game *game, t_player *player, char **map_arr)
{
	// printf("map_arr[%i][%i]\n", (int)(player->pos.x + player->dir.x * MOVESPEED), (int)(player->pos.y));
	// move forward
	// printf("player pos x: %f y: %f\n", player->pos.x, player->pos.y);
	if (keysym == W_KEY)
	{
		if (map_arr[(int)(player->pos.y)][(int)(player->pos.x + player->dir.x * MOVESPEED)] != '1')
			player->pos.x += player->dir.x * MOVESPEED;
		if (map_arr[(int)(player->pos.y + player->dir.y * MOVESPEED)][(int)(player->pos.x)] != '1')
			player->pos.y += player->dir.y * MOVESPEED;
	}
	// move backwards
	else if (keysym == S_KEY)
	{
		if (map_arr[(int)(player->pos.y)][(int)(player->pos.x - player->dir.x * MOVESPEED)] != '1')
			player->pos.x -= player->dir.x * MOVESPEED;
		if (map_arr[(int)(player->pos.y - player->dir.y * MOVESPEED)][(int)(player->pos.x)] != '1')
			player->pos.y -= player->dir.y * MOVESPEED;
	}
	render_frame(game, &game->player);
}