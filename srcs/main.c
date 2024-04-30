/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:42:38 by agan              #+#    #+#             */
/*   Updated: 2024/04/10 15:42:40 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game game;

	if (argc == 2)
	{
		game.mlx_ptr = mlx_init();
		init_map(&game, argv[1]);
		init_colors(&game, &game.map);
		init_textures(&game, &game.map);
		init_game(&game, &game.map);
		init_window(&game);
		draw_grid(&game, &game.map);
		raycast(&game, &game.player, &game.ray);
		render_to_window(&game, &game.minimap, 0, game.display.y);
		render_to_window(&game, &game.display, 0, 0);
		mlx_key_hook(game.win_ptr, key_handler, &game);
		mlx_hook(game.win_ptr, 17, 0, end_game, &game);
		mlx_loop(game.mlx_ptr);
	}
}
