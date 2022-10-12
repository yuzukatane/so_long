/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:15:13 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/12 22:11:16 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*read_map(t_map *map, int fd, char *filename)
{
	char	buf[128];
	char	*one_line_map = "\0";
	int		size;

	ft_bzero(buf, 128);
	while (1)
	{
		size = read(fd, buf, 127);
		if (size == -1)
		{
			free(one_line_map);
			free_and_exit(map, MAP_PTR);
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
	{
		ft_printf("File format is incorrect\n");
		return (FALSE);
	}
	return (TRUE);
}
//map.ber
t_map	*create_map(char *filename)
{
	t_map	*map;
	int		fd;
	char	*one_line_map;

	if (check_fileformat(filename) == FALSE)
		return (FALSE);
	map = malloc(sizeof(t_map));
	if (map == NULL)
		free_and_exit(map, NOTHING);
	
	fd = open(filename, O_RDONLY);

	//There is no such file.	free_and_exit()でメッセージ送る？エラーの時のメッセージ出力がバラバラすぎ！
	if (fd == -1)
		free_and_exit(map, MAP_PTR);
	one_line_map = read_map(map, fd, filename);

	map->array = ft_split(one_line_map, '\n');
	free(one_line_map);
	if (map->array == NULL)
		free_and_exit(map, MAP_PTR);

	if (check_map(map) == FALSE)
		free_and_exit(map, ARRAY);

	ft_printf("Map OK!\n");////消す
	return (map);
}
