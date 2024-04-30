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
# define EMPTY '0'

/* define minimap colours */
# define WALL_COLOR 0x264653
# define TILE_COLOR 0xFFEDDA
# define PLAYER_COLOR 0xAAAAA
# define RAY_COLOR 0xFF0000

/* define dimensions */
# define TILE_SIZE 32
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

enum e_dir
{
	N,
	S,
	E,
	W,
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

typedef struct s_ray
{
	t_pos	camera;
	t_pos	dir; //ray direction
	t_pos	sidedist;
	t_pos	deltadist;
	int 	perpwalldist;
	int 	lineheight;
	t_pos_i	map;
	t_pos_i	step;
	int 	side;
	int 	wall_found;
}	t_ray;

typedef struct s_player
{
	t_pos	pos;
	int		starting_dir;
	t_pos	dir; //player direction
	t_pos	plane; //camera plane of the player
}	t_player;

typedef struct s_map
{
	char	*map;
	char	**map_arr;
	int		fd;
	char	*textures[TEXTURE_COUNT];
	int		valid_no;
	int		valid_so;
	int		valid_ea;
	int		valid_we;
	int		valid_f;
	int		valid_c;
	int		map_height;
	int		map_width;
}	t_map;

typedef struct s_wall
{
	int start;
	int end;
}	t_wall;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		display;
	t_img		minimap;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_img		walls[4];
	int	*f_color;
	int	*c_color;
	unsigned int	floor;
	unsigned int	ceiling;
}	t_game;

/* color */
void	init_colors(t_game *game, t_map *map);
bool	is_whitespace(char c);

/* image utils */
void	render_to_window(t_game *game, t_img *image, int x, int y);
void	get_texture_info(t_img *texture);
void	new_texture(t_game *game, t_img *texture, char *path);
char	*get_pixel_pos(t_img *image, int x, int y);
void	ft_put_pixel(t_img *image, int x, int y, unsigned int colour);

/* draw */
void	draw_grid(t_game *game, t_map *map);
void	init_textures(t_game *game, t_map *map);
void	init_window(t_game *game);
int		is_player(char c);

/* init */
void	init_game(t_game *game, t_map *map);

/* init player */
void player_dir(t_player *player);
void	init_player(t_game *game, t_map *map);

/* misc */
int	key_handler(int keysym, t_game *game);
int	end_game(t_game *game);

/* map initialization */
int init_map(t_game *game, char *map_name);

/* draw ray */
void	draw_ray(t_img *display, t_ray *ray, t_player *player, char **map);

/* render wall */
void render_wall(t_game *game, t_ray *ray, int x);

/* map utils */
char	*strjoin_free(char *s1, char *s2);
void	free_arr(char **arr);
void	print_arr(char **arr);
char	**dup_map_arr(char **map_arr);
int		map_valid_syntax(char map_c);

/* map checker */
int map_checker(t_map *map, char **map_arr);

/* raycast */
void raycast(t_game *game, t_player *player, t_ray *ray);

/* texture checker */
char	*texture_whitespace(char *texture);
int		texture_parser(t_map *map, char **split_map);
int		texture_checker(t_map *map, char **split_map);

#endif
