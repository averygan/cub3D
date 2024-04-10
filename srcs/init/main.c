/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:42:38 by agan              #+#    #+#             */
/*   Updated: 2024/04/10 15:42:40 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* strjoin modified */
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

int main(int argc, char **argv)
{
	int fd;
	char *full_map;
	char *buf;
	
	str = NULL;
	buf = NULL;
	if (argc == 2)
	{
		str = ft_calloc(1, 1);
		fd = open(argv[1], O_RDONLY);
		while (1)
		{
			buf = get_next_line(fd);
			//printf("buf is now %s\n", buf);
			if (buf == NULL)
				break ;
			str = strjoin_free(str, buf);
			//printf("str is now %s\n", str);
		}
	}
	printf("%s\n", str);
}
