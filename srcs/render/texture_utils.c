/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:05:26 by yliew             #+#    #+#             */
/*   Updated: 2024/04/10 16:05:28 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Push the image to the window */
void	render_to_window(t_game *game, t_img *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		image->ptr, x, y);
}

/* Get the position of a pixel from the x and y coordinates */
char	*get_pixel_pos(t_img *image, int x, int y)
{
	return (image->addr + (y * image->line_size + x * (image->bpp / 8)));
}

/* Change the colour of a pixel on the mlx image */
void	ft_put_pixel(t_img *image, int x, int y, unsigned int colour)
{
	char	*pos;

	pos = get_pixel_pos(image, x, y);
	*(unsigned int *)pos = colour;
}
