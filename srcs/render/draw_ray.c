/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:15:09 by agan              #+#    #+#             */
/*   Updated: 2024/04/29 18:15:12 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}
/* Plot a line from the player position to where the ray hit the wall */
static void	dda_draw_ray(t_img *display, t_pos_i start, t_pos_i end, char **map)
{
	t_pos_i	delta;
	t_pos_i	step;
	int	slope_err;
	int	curr;

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
	slope_err = delta.x - delta.y;
	while ((start.x != end.x || start.y != end.y)
		&& map[(int)(start.y / TILE_SIZE)][(int)(start.x / TILE_SIZE)] != '1')
	{
		ft_put_pixel(display, start.x, start.y, 0xDC4444);
		curr = 2 * slope_err;
		if (curr > -delta.y)
		{
			slope_err -= delta.y;
			start.x += step.x;
		}
		if (curr < delta.x)
		{
			slope_err += delta.x;
			start.y += step.y;
		}
	}
}
/* Init structs for the start and end coordinates of the line to be drawn */
void	draw_ray(t_img *display, t_ray *ray, t_player *player, char **map)
{
	t_pos_i	start;
	t_pos_i	end;
	start.x = (int)player->pos.x * TILE_SIZE;
	start.y = (int)player->pos.y * TILE_SIZE;
	end.x = ray->map.x * TILE_SIZE;
	end.y = ray->map.y * TILE_SIZE;
	dda_draw_ray(display, start, end, map);
}