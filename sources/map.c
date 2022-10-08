/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:15:13 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/08 16:33:41 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	put_message_and_exit(void)
{
	ft_printf("Error\n");
	exit(1);
}

char	*read_map(int fd, char *filename)
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
			put_message_and_exit();
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

int	is_surrounded(char **map, int height, int width)
{
	int	i;
	int	counter;
	int	y;

	counter = 0;
	y = 0;
	while (counter < 2)
	{
		i = 0;
		while (map[y][i] != '\0')
		{
			if (map[y][i] != WALL)
					return (FALSE);
			i++;
		}
		y = height;
		counter++;
	}
	i = 1;
	while (i < height)
	{
		if (!(map[i][0] == WALL && map[i][width] == WALL))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_map(char **map)
{
	int	line_len;
	int	height;
	int	width;

	//横の長さが同じかチェック
	height = 0;
	line_len = ft_strlen(map[height]);
	while (map[height + 1] != NULL)
	{
		height++;
		if (line_len != ft_strlen(map[height]))
		{
			free_double_ptr(map);
			put_message_and_exit();
		}
	}
	//動くスペースが有るかチェック
	if (height < 2)
	{
		free_double_ptr(map);
		put_message_and_exit();
	}
	//壁に囲まれているかチェック
	width = line_len - 1;
	if (is_surrounded(map, height, width) == FALSE)
	{
			free_double_ptr(map);
			put_message_and_exit();
	}
	
	//P E C が一つ以上あるかチェック
	//指定された文字以外がないかチェック
	//ゴールにたどり着けるかチェック
	
	
	return (TRUE);
}

void	creat_map(char *filename)
{
	int		fd;
	char	**map;
	char	*one_line_map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		put_message_and_exit();
	one_line_map = read_map(fd, filename);
	map = ft_split(one_line_map, '\n');
	free(one_line_map);
	if (map == NULL)
	{
		put_message_and_exit();
	}

	if (check_map(map) == TRUE)
		ft_printf("OK!\n");
}
