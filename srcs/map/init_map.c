/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:33:14 by agan              #+#    #+#             */
/*   Updated: 2024/04/11 16:33:15 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* split map into individual lines
runn first 6 lines through texture checker */
int parse_map(t_game *game)
{
	char **split_map;
	split_map = ft_split(game->map.map, '\n');
	//print_arr(split_map);
	if (split_map)
	{
		texture_checker(game, split_map);
		map_checker(&game->map, &split_map[6]);
	}
	return 0;
}

void init_map_struct(t_game *game)
{
	int i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		game->map.textures[i] = NULL;
		i++;
	}
	game->map.map = NULL;
	game->map.map_arr = NULL;
	game->map.f_color = NULL;
	game->map.c_color = NULL;
	game->map.valid_no = 0;
	game->map.valid_so = 0;
	game->map.valid_ea = 0;
	game->map.valid_we = 0;
	game->map.valid_f = 0;
	game->map.valid_c = 0;
}

/* map initialization 
- check for .cub extension
- open .cub file
- get_next_line until EOF -> strjoin to full_map
- assign map.map to full_map
- run map parser to check and assign textures and map */
int init_map(t_game *game, char *map_name)
{
	int fd;
	char *full_map;
	char *buf;
	
	buf = NULL;
	full_map = ft_calloc(1, 1);
	init_map_struct(game);
	if (ft_strncmp(&map_name[ft_strlen(map_name) - 4], ".cub", 4))
		return (printf("invalid extension\n"));
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (printf("invalid file\n"));
	while (1)
	{
		buf = get_next_line(fd);
		//printf("buf is now %s\n", buf);
		if (buf == NULL)
			break ;
		full_map = strjoin_free(full_map, buf);
		//printf("str is now %s\n", str);
	}
	if (full_map)
	{
		game->map.map = full_map;
		// printf("printing map\n---------------------------------\n\n%s\n", full_map);
		parse_map(game);
	}
	return 0;
}