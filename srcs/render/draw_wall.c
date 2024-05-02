/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:52:00 by agan              #+#    #+#             */
/*   Updated: 2024/04/30 16:52:01 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void calc_perpdist(t_ray *ray)
// {
// 	if (ray->side == 0)
// 		ray->perpwalldist = ray->sidedist.x - ray->deltadist.x;
// 	else
// 		ray->perpwalldist = ray->sidedist.y - ray->deltadist.y;
// }

// void draw_wall(t_game *game, t_wall wall, int x)
// {
// 	int i;

// 	i = 0;
// 	while (i < game->display.y)
// 	{
// 		if (i < wall.start)
// 			ft_put_pixel(&game->display, x, i, game->ceiling);
// 		else if (i >= wall.start && i <= wall.end)
// 		{
// 			if (game->ray.side == 1)
// 				ft_put_pixel(&game->display, x, i, WALL_COLOR / 2);
// 			else
// 				ft_put_pixel(&game->display, x, i, WALL_COLOR);
// 		}
// 		else if (i > wall.end)
// 			ft_put_pixel(&game->display, x, i, game->floor);
// 		i++;
// 	}
// }

// void calc_wall(t_game *game, t_ray *ray, int x)
// {
// 	t_wall wall;
	
// 	wall.start = 0;
// 	wall.end = 0;
// 	// calc line of height to draw
// 	ray->lineheight = (int)(game->display.y / ray->perpwalldist);
// 	// calc highest and lowest pixel to fill in current stripe
// 	wall.start = -(ray->lineheight) / 2 + game->display.y / 2;
// 	if (wall.start < 0)
// 		wall.start = 0;
// 	wall.end = ray->lineheight / 2 + game->display.y / 2;
// 	if (wall.end >= game->display.y)
// 		wall.end = game->display.y - 1;
// 	// printf("start is %i, end is %i\n", wall.start, wall.end);
// 	draw_wall(game, wall, x);
// }

// void render_wall(t_game *game, t_ray *ray, int x)
// {
// 	calc_perpdist(ray);
// 	calc_wall(game, ray, x);
// }