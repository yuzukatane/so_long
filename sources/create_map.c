/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:15:13 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/23 11:30:52 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*read_map(t_map *map, int fd)
{
	char	buf[128];
	char	*one_line_map;
	int		size;

	ft_bzero(buf, 128);
	one_line_map = "\0";
	while (1)
	{
		size = read(fd, buf, 127);
		if (size == -1)
		{
			free(one_line_map);
			free_and_exit(map, MAP_PTR, "Failed to read the file");
		}
		one_line_map = ft_strjoin(one_line_map, buf);
		if (size < 127)
			break ;
		else
			ft_bzero(buf, 128);
	}
	close(fd);
	return (one_line_map);
}

int	check_fileformat(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(&filename[len - 4], ".ber", 4) != 0)
		return (FALSE);
	return (TRUE);
}

t_map	*create_map(char *filename)
{
	t_map	*map;
	int		fd;
	char	*one_line_map;

	map = NULL;
	if (check_fileformat(filename) == FALSE)
		free_and_exit(map, NOTHING, "File format is incorrect");
	map = malloc(sizeof(t_map));
	if (map == NULL)
		free_and_exit(map, NOTHING, "Failed to allocate memory");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		free_and_exit(map, MAP_PTR, "Failed to open the file");
	one_line_map = read_map(map, fd);
	map->array = ft_split(one_line_map, '\n');
	free(one_line_map);
	if (map->array == NULL)
		free_and_exit(map, MAP_PTR, "Failed to allocate memory");
	if (check_map(map) == FALSE)
		free_and_exit(map, ARRAY, "Map is incorrect");
	map->width++;
	map->height++;
	return (map);
}
