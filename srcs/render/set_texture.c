/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:53:49 by agan              #+#    #+#             */
/*   Updated: 2024/05/07 15:53:50 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* check which side the wall is facing and assign corresponding texture */
void	set_texture_pixel(t_game *game, t_ray *ray, t_wall *wall)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			wall->colors = game->walls[E_WE].colors;
		else
			wall->colors = game->walls[E_EA].colors;
	}
	else
	{
		if (ray->dir.y < 0)
			wall->colors = game->walls[E_SO].colors;
		else
			wall->colors = game->walls[E_NO].colors;
	}
}

/* wall_x: calculate where the wall was hit 
texture->x:
	- if (side == x && ray->dir.x > 0)
		ray hit the wall's x side on the positive side of x-axis
	- if (side == y && ray->dir.y < 0)
		ra hit the wall's y side on the negative side 
calculate step increment of the wall's y-coord for each pixel on screen */
void	calc_texture(t_game *game, t_ray *ray,
	t_player *player, t_wall *wall)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->pos.y + ray->perpwalldist * ray->dir.y;
	else
		wall_x = player->pos.x + ray->perpwalldist * ray->dir.x;
	wall_x -= floor(wall_x);
	wall->texture.x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == 0 && ray->dir.x > 0)
		wall->texture.x = TEXTURE_WIDTH - wall->texture.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		wall->texture.x = TEXTURE_WIDTH - wall->texture.x - 1;
	wall->step = 1.0 * TEXTURE_HEIGHT / ray->lineheight;
	wall->texpos = (wall->start - game->display.y / 2 + \
		ray->lineheight / 2) * wall->step;
}
