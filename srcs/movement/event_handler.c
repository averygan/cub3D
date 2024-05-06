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

int key_press_handler(int keysym, t_game *game)
{
	if (keysym == W_KEY || keysym == S_KEY)
		movement(keysym, game, &game->player, game->map.map_arr);
	else if (keysym == A_KEY || keysym == D_KEY)
		rotate(game, &game->player, keysym);
	return (0);
}