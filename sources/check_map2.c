/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:40:55 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/22 19:13:43 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	move(t_map *map, char **cpy, int x, int y)
{
	int	nx;
	int	ny;
	int	flag;

	if (x < 0 || map->width < x || y < 0
		|| map->height < y || cpy[y][x] == WALL)
		return (FALSE);
	if (cpy[y][x] == EXIT)
		return (TRUE);
	cpy[y][x] = PASSED;
	nx = x;
	ny = y - 1;
	if (ny >= 0 && cpy[ny][nx] != WALL && cpy[ny][nx] != PASSED)
	{
		flag = move(map, cpy, nx, ny);
		if (flag == TRUE)
			return (TRUE);
	}
	nx = x;
	ny = y + 1;
	if (ny <= map->height && cpy[ny][nx] != WALL && cpy[ny][nx] != PASSED)
	{
		flag = move(map, cpy, nx, ny);
		if (flag == TRUE)
			return (TRUE);
	}
	nx = x - 1;
	ny = y;
	if (nx >= 0 && cpy[ny][nx] != WALL && cpy[ny][nx] != PASSED)
	{
		flag = move(map, cpy, nx, ny);
		if (flag == TRUE)
			return (TRUE);
	}
	nx = x + 1;
	ny = y;
	if (nx <= map->width && cpy[ny][nx] != WALL && cpy[ny][nx] != PASSED)
	{
		flag = move(map, cpy, nx, ny);
		if (flag == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

char	**cpy_map(t_map *map)
{
	char	**cpy;
	int		height;
	int		i;

	height = map->height + 1 + 1;
	cpy = malloc(height * sizeof(char *));
	if (cpy == NULL)
		return (NULL);
	i = -1;
	while (++i < height - 1)
	{
		cpy[i] = ft_strdup(map->array[i]);
		if (cpy[i] == NULL)
		{
			while (0 <= i)
			{
				free(cpy[i]);
				i--;
			}
			free(cpy);
			return (NULL);
		}
	}
	cpy[i] = NULL;
	return (cpy);
}

int	is_there_a_valid_path(t_map *map, int x, int y)
{
	char	**cpy;

	cpy = cpy_map(map);
	if (cpy == NULL)
		return (FALSE);
	if (move(map, cpy, x, y) == TRUE)
	{
		free_double_ptr(cpy);
		return (TRUE);
	}
	else
	{
		free_double_ptr(cpy);
		return (FALSE);
	}
}
