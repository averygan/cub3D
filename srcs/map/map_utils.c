/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:13:28 by agan              #+#    #+#             */
/*   Updated: 2024/04/12 16:13:28 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* strjoin modified to free s1 and s2, returns a malloc'ed joined string */
char	*strjoin_free(char *s1, char *s2)
{
	char	*dst;
	size_t	d;
	size_t	i;

	d = ft_strlen(s1);
	dst = malloc((d + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[d + i] = s2[i];
	dst[d + i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (dst);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

/* function to get height and length, dup map arr */
char	**dup_map_arr(char **map_arr)
{
	int		i;
	char	**dup_arr;

	dup_arr = NULL;
	i = 0;
	while (map_arr[i])
		i++;
	dup_arr = malloc(sizeof(char *) * (i + 1));
	if (!dup_arr)
		return (NULL);
	i = 0;
	while (map_arr[i])
	{
		dup_arr[i] = ft_strdup(map_arr[i]);
		i++;
	}
	dup_arr[i] = NULL;
	return (dup_arr);
}

int	map_valid_syntax(char map_c)
{
	if (map_c != '1' && map_c != '0' && map_c != ' ' && map_c != '\n' \
		&& map_c != 'N' && map_c != 'S' && map_c != 'E' && map_c != 'W')
		return (-1);
	return (0);
}
