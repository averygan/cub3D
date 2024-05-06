/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:43:32 by yliew             #+#    #+#             */
/*   Updated: 2024/04/25 13:43:34 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arrays(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
}

void	free_color_arrays(unsigned int **array, int size)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
		free(array[i++]);
	if (array)
		free(array);
}

void	free_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < WALL_COUNT)
	{
		if (game->walls[i].ptr)
			mlx_destroy_image(game->mlx_ptr, game->walls[i].ptr);
		if (game->walls[i].colors)
			free_color_arrays(game->walls[i].colors, TEXTURE_WIDTH);
		i++;
	}
	if (game->display.ptr)
		mlx_destroy_image(game->mlx_ptr, game->display.ptr);
	if (game->minimap.ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.ptr);
}

void	free_colors(t_game *game)
{
	if (game->f_color)
		free(game->f_color);
	if (game->c_color)
		free(game->c_color);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (game->map.textures[i])
			free(game->map.textures[i]);
		i++;
	}
	if (game->map.map_arr)
		free_arrays(game->map.map_arr);
	if (game->map.map)
		free(game->map.map);
}
