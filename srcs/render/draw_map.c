/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:39:53 by yliew             #+#    #+#             */
/*   Updated: 2024/04/25 13:39:58 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_color(unsigned int *color, t_game *game, char **map, t_pos_i grid)
{
	int	row_width;

	row_width = ft_strlen(map[grid.y]);
	if (grid.x < row_width)
	{
		if (map[grid.y][grid.x] == WALL)
			*color = WALL_COLOR;
		else
			*color = game->floor;
	}
	else
		*color = game->floor;
}

/* Draw an individual tile on the map
- Check the map component to determine what colour to use
- Set the last column (end.x) as the start pos + the width of one tile
- For every row until the last row (end.y), 
draw one line until the end column */
void	draw_tile(t_game *game, char **map, t_pos_i grid, t_pos_i screen)
{
	unsigned int	current_color;
	int				start_column;
	t_pos_i			end;

	set_color(&current_color, game, map, grid);
	start_column = screen.x;
	end.x = screen.x + TILE_SIZE;
	end.y = screen.y + TILE_SIZE;
	while (screen.y < end.y)
	{
		screen.x = start_column;
		while (screen.x < end.x)
		{
			ft_put_pixel(&game->minimap, screen.x, screen.y, current_color);
			screen.x++;
		}
		screen.y++;
	}
}

/* Draw a circle on the minimap to represent the current player pos
- Find the coordinates of the centre of the circle
(player pos scaled to TILE_SIZE)
- Starting from the topmost row (y), calculate the width of each row
and fill every line from the initial current.x to the end.x value */
void	draw_player_pos(t_game *game, t_player *player)
{
	t_pos_i	centre;
	t_pos_i	current;
	t_pos_i	end;
	int		delta_x;

	centre.x = player->pos.x * TILE_SIZE;
	centre.y = player->pos.y * TILE_SIZE;
	current.y = centre.y - RADIUS;
	end.y = centre.y + RADIUS;
	while (current.y <= end.y)
	{
		delta_x = (int)sqrt(pow(RADIUS, 2) - pow(current.y - centre.y, 2));
		current.x = centre.x - delta_x;
		end.x = centre.x + delta_x;
		while (current.x <= end.x)
		{
			ft_put_pixel(&game->minimap, current.x, current.y, RAY_COLOR);
			current.x++;
		}
		current.y++;
	}
}

/* Draw the map on the display image and push to the window
- For every row, draw each tile individually */
void	draw_grid(t_game *game, t_map *map)
{
	int	row;
	int	column;

	row = 0;
	while (row < map->map_height)
	{
		column = 0;
		while (column < map->map_width)
		{
			draw_tile(game, map->map_arr,
				(t_pos_i){.x = column, .y = row},
				(t_pos_i){.x = column * TILE_SIZE, .y = row * TILE_SIZE});
			column++;
		}
		row++;
	}
	draw_player_pos(game, &game->player);
}
