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

void calc_perpdist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = ray->sidedist.x - ray->deltadist.x;
	else
		ray->perpwalldist = ray->sidedist.y - ray->deltadist.y;
}

void calc_wall(t_game *game, t_ray *ray, t_wall *wall)
{	
	wall->start = 0;
	wall->end = 0;
	calc_perpdist(ray);
	// calc line of height to draw
	ray->lineheight = (int)(game->display.y / ray->perpwalldist);
	// calc highest and lowest pixel to fill in current stripe
	wall->start = -ray->lineheight / 2 + game->display.y / 2;
	if (wall->start < 0)
		wall->start = 0;
	wall->end = ray->lineheight / 2 + game->display.y / 2;
	if (wall->end >= game->display.y)
		wall->end = game->display.y - 1;
}

void set_texture_pixel(t_game *game, t_ray *ray, t_wall *wall)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			wall->colors = game->walls[E_EA].colors;
		else
			wall->colors = game->walls[E_WE].colors;
	}
	else
	{
		if (ray->dir.y < 0)
			wall->colors = game->walls[E_NO].colors;
		else
			wall->colors = game->walls[E_SO].colors;
	}
}

void calc_texture(t_game *game, t_ray *ray, t_player *player, t_wall *wall)
{
	// calculate where the wall was hit
	double wall_x;

	if (ray->side == 0)
		wall_x = player->pos.y + ray->perpwalldist * ray->dir.y;
	else
		wall_x = player->pos.x + ray->perpwalldist * ray->dir.x;
	wall_x -= floor(wall_x);
	// x coord on the texture
	wall->texture.x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == 0 && ray->dir.x > 0)
		wall->texture.x = TEXTURE_WIDTH - wall->texture.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		wall->texture.x = TEXTURE_WIDTH - wall->texture.x - 1;
	wall->step = 1.0 * TEXTURE_HEIGHT / ray->lineheight;
	wall->texpos = (wall->start - game->display.y / 2 + ray->lineheight / 2) * wall->step;
}

void draw_floor_ceiling(t_game *game, t_wall wall, int x)
{
	int i;

	i = 0;
	while (i < game->display.y)
	{
		if (i < wall.start)
			ft_put_pixel(&game->display, x, i, game->ceiling);
		else if (i > wall.end)
			ft_put_pixel(&game->display, x, i, game->floor);
		i++;
	}
}

void draw_wall(t_game *game, t_ray *ray, t_wall *wall, int x)
{
	int i;
	unsigned int color;

	i = wall->start;
	// if (ray->side == 0)
		// printf("texture x is %i\n", wall->texture.x);
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

void render_wall(t_game *game, t_ray *ray, int x)
{
	calc_wall(game, ray, &ray->wall);
	// printf("start is %i, end is %i\n", wall.start, wall.end);
	set_texture_pixel(game, ray, &ray->wall);
	calc_texture(game, ray, &game->player, &game->ray.wall);
	draw_wall(game, ray, &ray->wall, x);
}