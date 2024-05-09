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
int	parse_map(t_game *game)
{
	char	**split_map;

	if (map_nl_checker(game->map.map, '\n') == -1)
		return (print_err(MAP_SYNTAX_ERR), -1);
	split_map = ft_split(game->map.map, '\n');
	if (!split_map)
		return (print_err(MEM_ERR), -1);
	if (texture_checker(&game->map, split_map))
		return (free_arrays(split_map), -1);
	if (map_checker(&game->map, &split_map[6]))
		return (free_arrays(split_map), -1);
	free_arrays(split_map);
	return (0);
}

void	init_map_struct(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		game->map.textures[i] = NULL;
		i++;
	}
	game->map.map = NULL;
	game->map.map_arr = NULL;
	game->map.valid_no = 0;
	game->map.valid_so = 0;
	game->map.valid_ea = 0;
	game->map.valid_we = 0;
	game->map.valid_f = 0;
	game->map.valid_c = 0;
	game->map.player_count = 0;
	game->map.map_height = 0;
	game->map.map_width = 0;
	game->map.tmp_map_width = 0;
}

char	*open_map(char *map_name)
{
	int		fd;
	char	*full_map;
	char	*buf;

	buf = NULL;
	full_map = ft_calloc(1, 1);
	if (!full_map)
		return (print_err(MEM_ERR), NULL);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (print_err(FILE_ERR), NULL);
	while (1)
	{
		buf = get_next_line(fd);
		if (buf == NULL)
			break ;
		full_map = strjoin_free(full_map, buf);
	}
	return (full_map);
}

/* map initialization 
- check for .cub extension
- open .cub file
- get_next_line until EOF -> strjoin to full_map
- assign map.map to full_map
- run map parser to check and assign textures and map */
int	init_map(t_game *game, char *map_name)
{
	char	*full_map;

	init_map_struct(game);
	if (ft_strncmp(&map_name[ft_strlen(map_name) - 4], ".cub", 4))
		return (print_err(FILE_EXT_ERR), -1);
	full_map = open_map(map_name);
	if (!full_map)
		return (-1);
	game->map.map = full_map;
	if (parse_map(game))
		return (-1);
	return (0);
}
