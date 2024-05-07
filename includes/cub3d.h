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

# include "raycast.h"
# include "error.h"
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

/* define keys */
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC 65307
# define ON_DESTROY 17
# define ON_MOUSEMOVE 6

/* define minimap colours and components */
# define WALL_COLOR 0x264653
# define TILE_COLOR 0xFFEDDA
# define LINE_COLOR 0x0C343D
# define RAY_COLOR 0xDC4444
# define TILE_SIZE 8
# define RADIUS 4

/* define dimensions */
# define SCREEN_WIDTH 960
# define SCREEN_HEIGHT 720
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define TEXTURE_COUNT 6
# define WALL_COUNT 4

/* define movement/rotation speed */
# define MOVESPEED 0.050
# define ROTSPEED 0.0150

/* text colour */
# define BROWN "\033[1;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

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

enum e_error
{
	MEM_ERR,
	MAP_SYNTAX_ERR,
	MAP_NOT_CLOSED_ERR,
	ELE_ERR,
	ELE_COUNT_ERR,
	FILE_EXT_ERR,
	FILE_ERR,
	TEXTURE_PATH_ERR,
	RGB_ERR,
	PLAYER_ERR,
};

/* structs */
typedef struct s_img
{
	void			*ptr;
	void			*addr;
	int				x;
	int				y;
	int				bpp;
	int				line_size;
	int				endian;
	unsigned int	**colors;
}	t_img;

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
	int		player_count;
	int		map_height;
	int		map_width;
	int		tmp_map_width;
}	t_map;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			display;
	t_img			minimap;
	t_map			map;
	t_player		player;
	t_ray			ray;
	t_img			walls[4];
	int				*f_color;
	int				*c_color;
	unsigned int	floor;
	unsigned int	ceiling;
}	t_game;

/* color */
int		init_colors(t_game *game, t_map *map);

/* image utils */
void	render_to_window(t_game *game, t_img *image, int x, int y);
void	get_texture_info(t_img *texture);
int		new_texture(t_game *game, t_img *texture, char *path);
char	*get_pixel_pos(t_img *image, int x, int y);
void	ft_put_pixel(t_img *image, int x, int y, unsigned int colour);

/* draw */
void	draw_grid(t_game *game, t_map *map);
int		init_textures(t_game *game, t_map *map);
int		init_window(t_game *game);
int		is_player(char c);

/* init */
int		init_game_struct(t_game *game);
void	init_game(t_game *game, t_map *map);

/* init player */
void	player_dir(t_player *player);
int		init_player_pos(t_map *map, t_player *player);

/* exit */
int		end_game(t_game *game, int exit_code);
int		close_window(t_game *game);

/* free data */
void	free_arrays(char **array);
void	free_images(t_game *game);
void	free_colors(t_game *game);
void	free_map(t_game *game);

/* error */
void	print_err(int err);
void	print_map_not_closed(int row, int col);

/* map initialization */
int		init_map(t_game *game, char *map_name);

/* map utils */
char	*strjoin_free(char *s1, char *s2);
void	free_arr(char **arr);
void	print_arr(char **arr);
char	**dup_map_arr(char **map_arr);
int		map_valid_syntax(char map_c);

/* map checker */
int		map_checker(t_map *map, char **map_arr);

/* checker utils */
char	**dup_tmp_map(t_map *map);
void	map_height_width(t_map *map, char **map_arr);
void	replace_map_spaces(char **map_arr);

/* texture checker */
char	*texture_whitespace(char *texture);
int		texture_parser(t_map *map, char **split_map);
int		texture_checker(t_map *map, char **split_map);

/* texture checker utils */
bool	is_whitespace(char c);
void	skip_texture_whitespace(char **split_map, int i, int *j);
bool	all_elements_found(t_map *map);
bool	all_textures_found(t_map *map);

/* movement */
int		key_press_handler(int keysym, t_game *game);
int		mouse_handler(int x, int y, t_game *game);
void	movement(int keysym, t_game *game, t_player *player, char **map_arr);
void	left_right_movement(int keysym, t_game *game, t_player *player, char **map_arr);
void	rotate_left(t_game *game, t_player *player);
void	rotate_right(t_game *game, t_player *player);

#endif
