/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:40:55 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/15 16:31:27 by kyuzu            ###   ########.fr       */
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

int	is_there_a_valid_path(t_map *map)
{
	if (move(map, map->array, map->start_pos[0], map->start_pos[1]) == TRUE)
		return (TRUE);
	else
		return (FALSE);
}
