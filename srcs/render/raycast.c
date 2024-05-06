/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:34:36 by agan              #+#    #+#             */
/*   Updated: 2024/04/23 14:34:38 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* raycasting algo:
ray starts at player position pos x, pos y 
calculate ray direction
camera x -> right = 1, center = 0, left = -1 
calculate sidedistX, sidedistY, deltadistX, deltadistY
	DDA
		if (sideDistX < sideDist)
			deltadistX until wall hit
		else
			deltadistY until wall hit 
		check if ray has hit a wall
calculate perpwalldist
	if side = x
		sidedistX - deltadistX
	if side = y
		sidedistY - deltadistY
calculate height of wall
	lineheight = (int)(h / perpwalldist)
*/

// void raycast(t_game *game, t_data *player, t_ray *ray)
// {
// 	player->dir.x = -1;
// 	player->dir.y = 0;
// 	ray->plane.x = 0; 
// 	ray->plane.y = 0.66;
// 	for (int x = 0; x < game->map.map_width; x++)
// 	{
// 		ray->camera.x = 2 * x / game->map.map_width - 1;
// 		ray->dir.x = ray->dir.x + ray->plane.x * ray->camera.x;
// 		ray->dir.y = ray->dir.y + ray->plane.y * ray->camera.x;
// 	}
// }

/* init ray variables */
void init_ray(t_ray *ray)
{
	ray->camera.x = 0;
	ray->camera.y = 0;
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->sidedist.x = 0;
	ray->sidedist.y = 0;
	ray->map.x = 0;
	ray->map.y = 0;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->side = 0;
	ray->lineheight = 0;
	ray->wall.dist = 0;
	ray->wall.start = 0;
	ray->wall.end = 0;
	ray->wall.texture.x = 0;
	ray->wall.texture.y = 0;
	ray->wall.step = 0;
	ray->wall.texpos = 0;
	ray->wall.colors = NULL;
}

/* function to calc step and initial sidedist of ray */
void calc_raycast(t_player player, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (player.pos.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - player.pos.x) * ray->deltadist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (player.pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - player.pos.y) * ray->deltadist.y;
	}
}

/* init each ray's data */
void init_raycast(t_player player, t_ray *ray, int x, int width)
{
	// calculate ray position and direction
	// x-coord in camera space
	ray->camera.x = 2 * x / (double)width - 1;
	ray->dir.x = player.dir.x + player.plane.x * ray->camera.x;
	ray->dir.y = player.dir.y + player.plane.y * ray->camera.x;
	// curr box position
	ray->map.x = (int)player.pos.x;
	ray->map.y = (int)player.pos.y;
	// length of ray from curr position to next x or y side
	if (ray->dir.x == 0)
		ray->deltadist.x = 1e30;
	else
		ray->deltadist.x = fabs(1/ray->dir.x);
	if (ray->dir.y == 0)
		ray->deltadist.y = 1e30;
	else
		ray->deltadist.y = fabs(1/ray->dir.y);
	// printf("dir y is %f\n", ray->dir.y);
	ray->wall_found = 0;
}

/* dda algorithm 
loop to check next box until wall met */
void dda(t_game *game, t_map *map, t_ray *ray)
{
	while (!ray->wall_found)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;			
		}
		if (map->map_arr[ray->map.y][ray->map.x] == '1')
		{
			// printf("wall found at %i, %i\n", ray->map.x, ray->map.y);
			ray->wall_found = 1;
			draw_ray(&game->minimap, ray, &game->player, game->map.map_arr);
		}
	}
}

/* raycasting loop */
void raycast(t_game *game, t_player *player, t_ray *ray)
{
	int i;

	i = 0;
	init_ray(ray);
	while (i < game->display.x)
	{
		init_raycast(*player, ray, i, game->display.x);
		calc_raycast(*player, ray);
		dda(game, &game->map, ray);
		// if (ray->side == 0)
		// 	printf("dir y is %f\n", ray->dir.y);
		render_wall(game, ray, i);
		i++;
	}
	render_to_window(game, &game->display, 0, 0);
}