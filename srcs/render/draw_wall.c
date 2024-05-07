/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:20:19 by agan              #+#    #+#             */
/*   Updated: 2024/05/02 13:20:20 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* calculate perpendicular distance from player to wall */
void	calc_perpdist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = ray->sidedist.x - ray->deltadist.x;
	else
		ray->perpwalldist = ray->sidedist.y - ray->deltadist.y;
}

/* calculate height of wall to be drawn 
lineheight = (int)(h/perpwalldist)
set wall start and end for y-coords of the wall line */
void	calc_wall(t_ray *ray, t_wall *wall)
{	
	wall->start = 0;
	wall->end = 0;
	calc_perpdist(ray);
	ray->lineheight = (int)(SCREEN_HEIGHT / ray->perpwalldist);
	wall->start = -ray->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (wall->start < 0)
		wall->start = 0;
	wall->end = ray->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (wall->end >= SCREEN_HEIGHT)
		wall->end = SCREEN_HEIGHT - 1;
}

/* draw the floor and ceiling, skip over wall */
void	draw_floor_ceiling(t_game *game, t_wall wall, int x)
{
	int	i;

	i = 0;
	while (i <= SCREEN_HEIGHT)
	{
		if (i < wall.start)
			ft_put_pixel(&game->display, x, i, game->ceiling);
		else if (i > wall.end)
			ft_put_pixel(&game->display, x, i, game->floor);
		i++;
	}
}

/* Texture mapping to the current vertical strip (column) of the wall
- Loop over every y-coordinate from the start to the end of the wall strip
- Get the color of the pixel to draw
- Adjust darker color for shading:
	- RGB >> 1 & bitmask to get the correct value
	- 011111110111111101111111 = 8355711 in decimal
- Set the pixel on the game display */
void	draw_wall(t_game *game, t_ray *ray, t_wall *wall, int x)
{
	int				i;
	unsigned int	color;

	i = wall->start;
	while (i < wall->end)
	{
		wall->texture.y = (int)wall->texpos & (TEXTURE_HEIGHT - 1);
		wall->texpos += wall->step;
		color = wall->colors[wall->texture.x][wall->texture.y];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		ft_put_pixel(&game->display, x, i, color);
		i++;
	}
	draw_floor_ceiling(game, *wall, x);
}

void	render_wall(t_game *game, t_ray *ray, int x)
{
	calc_wall(ray, &ray->wall);
	set_texture_pixel(game, ray, &ray->wall);
	calc_texture(game, ray, &game->player, &game->ray.wall);
	draw_wall(game, ray, &ray->wall, x);
}
