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

void	start_game(t_game *game)
{
	movement(W_KEY, game, &game->player, game->map.map_arr);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_press_handler, game);
	mlx_hook(game->win_ptr, ON_MOUSEMOVE, PointerMotionMask, \
		mouse_handler, game);
	mlx_hook(game->win_ptr, ON_DESTROY, 0, close_window, game);
	mlx_loop(game->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		if (!init_game_struct(&game) && \
			!init_map(&game, argv[1]) && \
			!init_colors(&game, &game.map) && \
			!init_textures(&game, &game.map) && \
			!init_player_pos(&game.map, &game.player) && \
			!init_window(&game))
		{
			render_frame(&game, &game.player);
			start_game(&game);
		}
		end_game(&game, EXIT_FAILURE);
	}
	else
		print_err(ARGC_ERR);
}
