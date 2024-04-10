/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:03:59 by yliew             #+#    #+#             */
/*   Updated: 2024/04/10 16:04:17 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	test_map[MAP_HEIGHT][MAP_WIDTH] =
{
	"111111",
	"100001",
	"111101",
	"110001",
	"100001",
	"111111"
};

void	init_window(t_game *game)
{
	game->display.x = MAP_WIDTH * TILE_SIZE;
	game->display.y = MAP_HEIGHT * TILE_SIZE;
	game->win_ptr = mlx_new_window(game->mlx_ptr,
		game->display.x, game->display.y, "cub3d");
	game->display.ptr = mlx_new_image(game->mlx_ptr,
		game->display.x, game->display.y);
	get_texture_info(&game->display);
}

void	init_textures(t_game *game, t_map *map)
{
	map->no_path = "./assets/wolfenstein/xpm/grey_stone.xpm";
	map->so_path = "./assets/wolfenstein/xpm/mossy.xpm";
	map->ea_path = "./assets/wolfenstein/xpm/color_stone.xpm";
	map->we_path = "./assets/wolfenstein/xpm/color_stone.xpm";
	new_texture(game, &map->walls[no], map->no_path);
	new_texture(game, &map->walls[so], map->so_path);
	new_texture(game, &map->walls[ea], map->ea_path);
	new_texture(game, &map->walls[we], map->we_path);
}

/* temp values for testing */
void	init_colours(t_map *map)
{
	map->f_color = malloc(sizeof(int));
	map->f_color[0] = 153;
	map->f_color[1] = 153;
	map->f_color[2] = 153; //0x999999
	map->c_color = malloc(sizeof(int));
	map->c_color[0] = 238;
	map->c_color[1] = 238;
	map->c_color[2] = 238; //0xeeeeee
	map->floor = new_rgb(map->f_color);
	map->ceiling = new_rgb(map->c_color);
}

int	main(void)
{
	t_game	game;

	game.mlx_ptr = mlx_init();
	init_window(&game);
	init_textures(&game, &game.map);
	init_colours(&game.map);
	draw_grid(&game, &game.display);
	render_to_window(&game, &game.display, 0, 0);
	game.player.pos.x = 3;
	game.player.pos.y = 4;
	// render_to_window(&game, &game.map.walls[so],
	// 	game.player.pos.x * TILE_SIZE, game.player.pos.y * TILE_SIZE);
	game.player.direction.x = -1;
	game.player.direction.y = 0;
	game.player.plane.x = 0;
	game.player.plane.y = 0.66;
	mlx_key_hook(game.win_ptr, key_handler, &game);
	mlx_hook(game.win_ptr, 17, 0, end_game, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
