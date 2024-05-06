/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:54:21 by agan              #+#    #+#             */
/*   Updated: 2024/05/06 17:54:23 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_frame(t_game *game, t_player *player)
{
	draw_grid(game, &game->map);
	raycast(game, player, &game->ray);
	render_to_window(game, &game->display, 0, 0);
	render_to_window(game, &game->minimap, 0, SCREEN_HEIGHT - game->minimap.y);
}

/* Return the absolute value of a number */
int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int	is_player(char c)
{
	if (c == 'N')
		return (N);
	else if (c == 'S')
		return (S);
	else if (c == 'E')
		return (E);
	else if (c == 'W')
		return (W);
	else
		return (-1);
}