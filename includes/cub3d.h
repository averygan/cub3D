/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:43 by yliew             #+#    #+#             */
/*   Updated: 2024/04/10 16:06:45 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../mlx_linux/mlx.h"

/* define map components */
# define WALL '1'

/* define dimensions */
# define MAP_HEIGHT 6
# define MAP_WIDTH 6
# define TILE_SIZE 100

/* structs */

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	int		x;
	int		y;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_ray
{
	t_pos	camera;
	t_pos	direction; //ray direction
}	t_ray;

typedef struct s_data
{
	t_pos	pos;
	t_pos	direction; //player direction
	t_pos	plane; //camera plane of the player
	double	current_time; //time of current frame (to calculate fps)
	double	prev_time; //time of prev frame
}	t_data;


typedef struct s_map
{
	char	**map_arr;
	int		fd;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	int		*f_color;
	int		*c_color;
}	t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	display;
	t_map	map;
	t_data	player;
	t_ray	ray;
	int		screen_x;
	int		screen_y;
}	t_game;

/* graphics */
void			render_to_window(t_game *game, t_img *image, int x, int y);
void			get_texture_info(t_img *texture);
void			new_texture(t_game *game, t_img *texture, char *path);
unsigned int	get_pixel_pos(t_img *image, int x, int y);

#endif
