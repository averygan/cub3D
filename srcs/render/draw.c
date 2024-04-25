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

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	draw_line(t_img *display, t_pos_i start, t_pos_i end)
{
	t_pos_i	delta;
	t_pos_i	step;
	int		slope_error;
	int		curr_error;

	delta.x = ft_abs(end.x - start.x);
	delta.y = ft_abs(end.y - start.y);
	if (start.x < end.x)
		step.x = 1;
	else
		step.x = -1;
	if (start.y < end.y)
		step.y = 1;
	else
		step.y = -1;
	slope_error = delta.x - delta.y;
	while (start.x != end.x || start.y != end.y)
	{
		ft_put_pixel(display, start.x, start.y, 0xDC4444);
		curr_error = 2 * slope_error;
		if (curr_error > -delta.y)
		{
			slope_error -= delta.y;
			start.x += step.x;
		}
		if (curr_error < delta.x)
		{
			slope_error += delta.x;
			start.y += step.y;
		}
	}
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	draw_tile(t_game *game, t_map *map, t_pos_i grid, t_pos_i screen)
{
	unsigned int	current_color;
	int				start_column;
	t_pos_i			end;

	start_column = screen.x;
	if (map->map_arr[grid.y][grid.x] == WALL)
		current_color = WALL_COLOR; // current_color = game->map.floor;
	else if (map->map_arr[grid.y][grid.x] == EMPTY
		|| is_player(map->map_arr[grid.y][grid.x]))
		current_color = TILE_COLOR; // current_color = game->map.ceiling;
	else
		return ;
	end.x = screen.x + TILE_SIZE;
	end.y = screen.y + TILE_SIZE;
	while (screen.y < end.y)
	{
		screen.x = start_column;
		while (screen.x < end.x)
		{
			if (screen.x % TILE_SIZE == 0 || screen.y % TILE_SIZE == 0)
				ft_put_pixel(&game->display, screen.x, screen.y, 0x0c343d);
			else
				ft_put_pixel(&game->display, screen.x, screen.y, current_color);
			screen.x++;
		}
		screen.y++;
	}
}

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
			draw_tile(game, map,
				(t_pos_i){.x = column, .y = row},
				(t_pos_i){.x = column * TILE_SIZE, .y = row * TILE_SIZE});
			column++;
		}
		row++;
	}
	// draw_line(display, (t_pos_i){.x = TILE_SIZE, .y = TILE_SIZE},
	// 	(t_pos_i){.x = 20 * TILE_SIZE, .y = 10 * TILE_SIZE});
	render_to_window(game, &game->display, 0, 0);
}
