/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
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
	// printf("R: %i, G: %i, B: %i\n", color[R], color[G], color[B]);
	return (color[R] << 16 | color[G] << 8 | color[B]);
}

/*
- skip whitespaces before/after numbers, before/after comma */
char	**split_rgb(char *str, int size)
{
	char	**arr;
	int		i;
	int		len;

	arr = malloc((size + 1) * sizeof(char));
	i = 0;
	while (i < size)
	{
		while (*str && is_whitespace(*str))
			str++;
		len = 0;
		while (str[len] && ft_isdigit(str[len]))
			len++;
		arr[i] = ft_substr(str, 0, len);
		str += len;
		while (*str && is_whitespace(*str))
			str++;
		if (i != size - 1)
			if (*str && *str == ',')
				str++;
		while (*str && is_whitespace(*str))
			str++;
		if (*str && !is_whitespace(*str) && !ft_isdigit(*str))
		{
			printf("error: [%c] %s\n\n", *str, str);
			// print_err("Invalid RGB value.\n");
			break ;
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/* to add:
- backtrack free
- error message */
int	parse_colors(char *str, int **rgb_arr)
{
	char	**arr;
	int		i;

	arr = split_rgb(str, 3);
	*rgb_arr = malloc(3 * sizeof(int));
	if (!*rgb_arr)
		return (-1); //and print error
	i = 0;
	while (arr[i])
	{
		(*rgb_arr)[i] = ft_atoi(arr[i]);
		i++;
	}
	return (0);
}

// int	parse_colors(char *str, int **rgb_arr)
// {
// 	char	**arr;
// 	int		size;
// 	int		i;

// 	arr = ft_split(str, ',');
// 	size = 0;
// 	while (arr[size])
// 		size++;
// 	if (size != 3)
// 		return (-1); //and print error
// 	*rgb_arr = malloc(size * sizeof(int));
// 	if (!*rgb_arr)
// 		return (-1); //and print error
// 	i = 0;
// 	while (arr[i])
// 	{
// 		(*rgb_arr)[i] = ft_atoi(arr[i]);
// 		i++;
// 	}
// 	return (0);
// }

/* Extract RGB values from string and combine them into an unsigned int */
void	init_colors(t_game *game, t_map *map)
{
	int *f_color;
	int *c_color;

	if (parse_colors(map->textures[E_F], &f_color) != -1)
	{
		game->floor = new_rgb(f_color);
		free(f_color);
	}
	if (parse_colors(map->textures[E_C], &c_color) != -1)
	{
		game->ceiling = new_rgb(c_color);
		free(c_color);
	}
	printf("floor: %u\nceiling: %u\n", game->floor, game->ceiling);
}