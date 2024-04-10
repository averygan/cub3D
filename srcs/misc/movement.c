/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:40:42 by yliew             #+#    #+#             */
/*   Updated: 2024/04/10 16:40:47 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		end_game(game);
	return (0);
}

/*
int	key_handler(int keysym, t_game *game)
{
	set_pos(&game->player.prev, game->player.current.x,
		game->player.current.y);
	if (keysym == XK_w || keysym == XK_Up)
		player_movement(game, &game->map, &game->player.current, up);
	else if (keysym == S_KEY || keysym == DOWN_KEY)
		player_movement(game, &game->map, &game->player.current, down);
	else if (keysym == A_KEY || keysym == LEFT_KEY)
		player_movement(game, &game->map, &game->player.current, left);
	else if (keysym == D_KEY || keysym == RIGHT_KEY)
		player_movement(game, &game->map, &game->player.current, right);
	else if (keysym == ESC)
		end("Quitting game.\n", game, 0);
	return (0);
}
*/
