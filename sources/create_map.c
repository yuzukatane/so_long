/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:15:13 by kyuzu             #+#    #+#             */
/*   Updated: 2022/12/10 17:31:52 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_empty_line(char *one_line_map)
{
	int	i;

	i = 0;
	while (one_line_map[i] == '\n')
		i++;
	while (one_line_map[i] != '\0')
	{
		if (one_line_map[i] == '\n' && one_line_map[i + 1] == '\n')
		{
			while (one_line_map[i] == '\n')
				i++;
			if (one_line_map[i] != '\0')
				return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}

char	*read_map(t_map *map, char *filename)
{
	int		fd;
	char	buf[128];
	char	*one_line_map;
	int		size;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		free_and_exit(map, MAP_PTR, "Error\nFailed to open the file\n");
	one_line_map = "\0";
	while (1)
	{
		ft_bzero(buf, 128);
		size = read(fd, buf, 127);
		if (size == -1)
		{
			free(one_line_map);
			free_and_exit(map, MAP_PTR, "Error\nFailed to read the file\n");
		}
		one_line_map = ft_strjoin(one_line_map, buf);
		if (size < 127)
			break ;
	}
	close(fd);
	return (one_line_map);
}

int	check_fileformat(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(&filename[len - 4], ".ber", 4) != 0
		|| ft_strncmp(&filename[len - 5], "/.ber", 5) == 0)
		return (FALSE);
	return (TRUE);
}

t_map	*create_map(char *filename)
{
	t_map	*map;
	char	*one_line_map;

	map = NULL;
	if (check_fileformat(filename) == FALSE)
		free_and_exit(map, NOTHING, "Error\nFile format is incorrect\n");
	map = malloc(sizeof(t_map));
	if (map == NULL)
		free_and_exit(map, NOTHING, "Error\nFailed to allocate memory\n");
	one_line_map = read_map(map, filename);
	if (check_empty_line(one_line_map) == FALSE)
	{
		free(one_line_map);
		free_and_exit(map, MAP_PTR, "Error\nMap is incorrect\n");
	}
	map->array = ft_split(one_line_map, '\n');
	free(one_line_map);
	if (map->array == NULL || *map->array == NULL)
		free_and_exit(map, MAP_PTR, "Error\nMap is incorrect\n");
	if (check_map(map) == FALSE)
		free_and_exit(map, ARRAY, "Error\nMap is incorrect\n");
	map->width++;
	map->height++;
	return (map);
}
