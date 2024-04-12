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

#include "../includes/cub3d.h"

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
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		dst[d + i] = s2[i];
		i++;
	}
	dst[d + i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (dst);
}

void free_arr(char **arr)
{
	int i;

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

void print_arr(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("arr[%i] -> %s\n", i, arr[i]);
		i++;
	}
}