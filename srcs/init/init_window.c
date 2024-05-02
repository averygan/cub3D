/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:40:32 by yliew             #+#    #+#             */
/*   Updated: 2024/04/25 13:40:34 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Create a blank mlx image for drawing pixel by pixel */
void	new_canvas(t_game *game, t_img *image)
{
	image->ptr = mlx_new_image(game->mlx_ptr,
		game->display.x, game->display.y);
	get_texture_info(image);
}

/* Create window based on the dimensions of the map */
void	init_window(t_game *game)
{
	game->display.x = game->map.map_width * TILE_SIZE;
	game->display.y = game->map.map_height * TILE_SIZE;
	game->win_ptr = mlx_new_window(game->mlx_ptr,
		game->display.x, game->display.y * 2, "cub3d");
	new_canvas(game, &game->display);
	new_canvas(game, &game->minimap);
	get_texture_info(&game->display);
}
