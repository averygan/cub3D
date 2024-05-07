/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:24:16 by agan              #+#    #+#             */
/*   Updated: 2024/05/06 13:24:16 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_handler(int x, int y, t_game *game)
{
	static int	old_x;

	(void)y;
	if (x > old_x)
		rotate_right(game, &game->player);
	else if (x < old_x)
		rotate_left(game, &game->player);
	old_x = x;
	return (0);
}

int	key_press_handler(int keysym, t_game *game)
{
	if (keysym == W_KEY || keysym == S_KEY)
		movement(keysym, game, &game->player, game->map.map_arr);
	if (keysym == A_KEY || keysym == D_KEY)
		left_right_movement(keysym, game, &game->player, game->map.map_arr);
	else if (keysym == LEFT_KEY)
		rotate_left(game, &game->player);
	else if (keysym == RIGHT_KEY)
		rotate_right(game, &game->player);
	else if (keysym == XK_Escape)
		end_game(game, EXIT_SUCCESS);
	return (0);
}
