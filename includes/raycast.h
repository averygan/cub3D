/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:51:30 by yliew             #+#    #+#             */
/*   Updated: 2024/04/25 13:51:31 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_game t_game;

typedef struct s_map t_map;

typedef struct s_img t_img;

typedef struct s_pos_i
{
	int	x;
	int	y;
}	t_pos_i;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_wall
{
	double		dist;
	int 		start;
	int			end;
	t_pos_i		texture;
	double		step;
	double		texpos;
	unsigned int	**colors;
}	t_wall;

typedef struct s_ray
{
	t_pos	camera;
	t_pos	dir; //ray direction
	t_pos	sidedist;
	t_pos	deltadist;
	double 	perpwalldist;
	int 	lineheight;
	t_pos_i	map;
	t_pos_i	step;
	int 	side;
	int 	wall_found;
	t_wall	wall;
}	t_ray;

typedef struct s_player
{
	int		starting_dir;
	t_pos	pos;
	t_pos	dir; //player direction
	t_pos	plane; //camera plane of the player
}	t_player;

/* draw ray */
void	draw_ray(t_img *display, t_ray *ray, t_player *player, char **map);

/* raycast */
void	raycast(t_game *game, t_player *player, t_ray *ray);

/* render wall */
void	render_wall(t_game *game, t_ray *ray, int x);

/* render utils */
void	render_frame(t_game *game, t_player *player);

void	draw_player_pos(t_game *game, t_player *player);

#endif
