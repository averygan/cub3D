/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:23:12 by yliew             #+#    #+#             */
/*   Updated: 2024/04/23 19:23:22 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	new_rgb(int *color)
{
	return (color[R] << 16 | color[G] << 8 | color[B]);
}

void	skip_whitespace(char **str)
{
	while (**str && is_whitespace(**str))
		(*str)++;
}

/* Valid string: 3 numbers separated by comma
- skip whitespaces before/after numbers, before/after comma */
char	**split_rgb(char *str, int size)
{
	char	**arr;
	int		i;
	int		len;

	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (print_err(MEM_ERR), NULL);
	i = -1;
	while (++i < size)
	{
		skip_whitespace(&str);
		len = 0;
		while (str[len] && ft_isdigit(str[len]))
			len++;
		arr[i] = ft_substr(str, 0, len);
		str += len;
		skip_whitespace(&str);
		if (i != size - 1 && *str && *str == ',')
			str++;
		skip_whitespace(&str);
		if (*str && !is_whitespace(*str) && !ft_isdigit(*str))
			return (free_arrays(arr), print_err(RGB_ERR), NULL);
	}
	arr[i] = NULL;
	return (arr);
}

int	parse_colors(char *str, int **rgb_arr)
{
	char	**arr;
	int		i;

	arr = split_rgb(str, 3);
	if (!arr)
		return (-1);
	*rgb_arr = malloc(3 * sizeof(int));
	if (!*rgb_arr)
		return (free_arrays(arr),
			print_err(MEM_ERR), -1);
	i = 0;
	while (arr[i])
	{
		(*rgb_arr)[i] = ft_atoi(arr[i]);
		i++;
	}
	free_arrays(arr);
	return (0);
}

/* Extract RGB values from string and combine them into an unsigned int */
int	init_colors(t_game *game, t_map *map)
{
	if (parse_colors(map->textures[E_F], &game->f_color) != -1)
		game->floor = new_rgb(game->f_color);
	else
		return (-1);
	if (parse_colors(map->textures[E_C], &game->c_color) != -1)
		game->ceiling = new_rgb(game->c_color);
	else
		return (-1);
	return (0);
}
