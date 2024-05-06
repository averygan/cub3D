/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:57:38 by agan              #+#    #+#             */
/*   Updated: 2024/04/25 14:57:38 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Call mlx_get_data_addr to get the info of the specified image */
void	get_texture_info(t_img *texture)
{
	texture->addr = mlx_get_data_addr(texture->ptr, &texture->bpp,
			&texture->line_size, &texture->endian);
}

/* Create a 2D array of every pixel color in the texture
- Stores the values by column, since walls are drawn vertically */
int	store_texture_colors(t_img *texture)
{
	char	*pos;
	int		x;
	int		y;

	texture->colors = malloc(TEXTURE_WIDTH * sizeof(unsigned int *));
	if (!texture->colors)
		return (print_err(MEM_ERR), -1);
	x = 0;
	while (x < TEXTURE_WIDTH)
	{
		y = 0;
		texture->colors[x] = malloc(TEXTURE_HEIGHT * sizeof(unsigned int));
		if (!texture->colors[x])
			return (print_err(MEM_ERR), -1);
		while (y < TEXTURE_HEIGHT)
		{
			pos = get_pixel_pos(texture, x, y);
			texture->colors[x][y] = *(unsigned int *)pos;
			y++;
		}
		x++;
	}
	return (0);
}

/* Create an image from a file path and initialise its info in the struct */
int	new_texture(t_game *game, t_img *texture, char *path)
{
	texture->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&texture->x, &texture->y);
	if (!texture->ptr)
		return (print_err(TEXTURE_PATH_ERR), -1);
	get_texture_info(texture);
	texture->colors = NULL;
	if (store_texture_colors(texture) == -1)
		return (-1);
	return (0);
}

/* Initialise the wall textures for each direction */
int	init_textures(t_game *game, t_map *map)
{
	if (new_texture(game, &game->walls[E_NO], map->textures[E_NO])
		|| new_texture(game, &game->walls[E_SO], map->textures[E_SO])
		|| new_texture(game, &game->walls[E_EA], map->textures[E_EA])
		|| new_texture(game, &game->walls[E_WE], map->textures[E_WE]))
		return (-1);
	return (0);
}