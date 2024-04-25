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
# define TEXTURE_COUNT 6

enum e_textures
{
	E_NO,
	E_SO,
	E_EA,
	E_WE,
	E_F,
	E_C,
};

enum e_rgb
{
	R,
	G,
	B,
};

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
	char	*map;
	char	**map_arr;
	int		fd;
	char	*textures[TEXTURE_COUNT];
	t_img	walls[4];
	int	*f_color;
	int	*c_color;
	unsigned int	floor;
	unsigned int	ceiling;
	int		valid_no;
	int		valid_so;
	int		valid_ea;
	int		valid_we;
	int		valid_f;
	int		valid_c;
	int		map_height;
	int		map_width;
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

extern	char	test_map[MAP_HEIGHT][MAP_WIDTH];

/* color */
void	init_colors(t_map *map);

/* image utils */
void	render_to_window(t_game *game, t_img *image, int x, int y);
void	get_texture_info(t_img *texture);
void	new_texture(t_game *game, t_img *texture, char *path);
char	*get_pixel_pos(t_img *image, int x, int y);
unsigned int	new_rgb(int *colors);
void	draw_grid(t_game *game, t_img *display);
void	init_textures(t_game *game, t_map *map);
void	init_window(t_game *game);

/* misc */
int	key_handler(int keysym, t_game *game);
int	end_game(t_game *game);

/* map initialization */
int		init_map(t_game *game, char *map_name);

/* map utils */
char	*strjoin_free(char *s1, char *s2);
void	free_arr(char **arr);
void	print_arr(char **arr);
char	**dup_map_arr(char **map_arr);
int		map_valid_syntax(char map_c);

/* map checker */
int map_checker(t_map *map, char **map_arr);

/* texture checker */
char	*texture_whitespace(char *texture);
int		texture_parser(t_map *map, char **split_map);
int		texture_checker(t_map *map, char **split_map);

#endif
