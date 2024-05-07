/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:01:12 by agan              #+#    #+#             */
/*   Updated: 2024/04/12 16:01:12 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err_message(int err)
{
	if (err == MEM_ERR)
		ft_putstr_fd("Memory allocation failed.\n", 2);
	else if (err == MAP_SYNTAX_ERR)
		ft_putstr_fd("Map contains invalid characters.\n", 2);
	else if (err == FILE_EXT_ERR)
		ft_putstr_fd("Invalid file extension.\n", 2);
	else if (err == FILE_ERR)
		ft_putstr_fd("Invalid file.\n", 2);
	else if (err == ELE_ERR)
		ft_putstr_fd("Map contains invalid elements.\n", 2);
	else if (err == ELE_COUNT_ERR)
		ft_putstr_fd("Map does not contain all required elements.\n", 2);
	else if (err == TEXTURE_PATH_ERR)
		ft_putstr_fd("Invalid texture path.\n", 2);
	else if (err == RGB_ERR)
		ft_putstr_fd("Invalid RGB value.\n", 2);
	else if (err == PLAYER_ERR)
		ft_putstr_fd("Map must contain 1 player.\n", 2);
	else if (err == ARGC_ERR)
		ft_putstr_fd("./cub3D [file_name.cub]\n", 2);
}

void	print_err(int err)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	print_err_message(err);
	ft_putstr_fd(RESET, 2);
}

void	print_map_not_closed(int row, int col)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Map not closed at [", 2);
	ft_putnbr_fd(row, 2);
	ft_putstr_fd("][", 2);
	ft_putnbr_fd(col, 2);
	ft_putstr_fd("].\n", 2);
	ft_putstr_fd(RESET, 2);
}
