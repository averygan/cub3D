/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:05:26 by yliew             #+#    #+#             */
/*   Updated: 2024/04/10 16:05:28 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_to_window(t_game *game, t_img *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		image->ptr, x, y);
}

void	get_texture_info(t_img *texture)
{
	texture->addr = mlx_get_data_addr(texture->ptr, &texture->bpp,
			&texture->line_size, &texture->endian);
}

void	new_texture(t_game *game, t_img *texture, char *path)
{
	texture->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&texture->x, &texture->y);
	get_texture_info(texture);
}

char	*get_pixel_pos(t_img *image, int x, int y)
{
	return (image->addr + (y * image->line_size + x * (image->bpp / 8)));
}

/* r = colour[0], g = colour[1], b = colour[2] */
unsigned int	new_rgb(int *colour)
{
	return (colour[0] << 16 | colour[1] << 8 | colour[2]);
}

void	draw_tile(t_game *game, t_img *display, int grid_x, int display_y)
{
	unsigned int	current_colour;
	char			*pos;
	int	start_display_x;
	int	display_x;
	int	end_x;
	int	end_y;

	display_x = grid_x * TILE_SIZE;
	start_display_x = display_x;
	if (test_map[display_y / TILE_SIZE][grid_x] == WALL)
		current_colour = game->map.floor;
	else
		current_colour = game->map.ceiling;
	end_x = display_x + TILE_SIZE;
	end_y = display_y + TILE_SIZE;
	while (display_y < end_y)
	{
		display_x = start_display_x;
		while (display_x < end_x)
		{
			pos = get_pixel_pos(display, display_x, display_y);
			if (display_x % TILE_SIZE == 0 || display_y % TILE_SIZE == 0)
				*(unsigned int *)pos = 0x0c343d;
			else
				*(unsigned int *)pos = current_colour;
			display_x++;
		}
		display_y++;
	}
}

void	draw_grid(t_game *game, t_img *display)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			draw_tile(game, display, x, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}