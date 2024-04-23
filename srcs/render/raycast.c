/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:34:36 by agan              #+#    #+#             */
/*   Updated: 2024/04/23 14:34:38 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* raycasting algo:
ray starts at player position pos x, pos y 
calculate ray direction
camera x -> right = 1, center = 0, left = -1 
calculate sidedistX, sidedistY, deltadistX, deltadistY
	DDA
		if (sideDistX < sideDist)
			deltadistX until wall hit
		else
			deltadistY until wall hit 
		check if ray has hit a wall
calculate perpwalldist
	if side = x
		sidedistX - deltadistX
	if side = y
		sidedistY - deltadistY
calculate height of wall
	lineheight = (int)(h / perpwalldist)
*/
