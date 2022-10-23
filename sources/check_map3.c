/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:25:49 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/23 11:31:38 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	up(t_map *map, char **cpy, int x, int y)
{
	int	nx;
	int	ny;
	int	flag;

	nx = x;
	ny = y - 1;
	if (ny >= 0 && cpy[ny][nx] != WALL && cpy[ny][nx] != PASSED)
	{
		flag = move(map, cpy, nx, ny);
		if (flag == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

int	down(t_map *map, char **cpy, int x, int y)
{
	int	nx;
	int	ny;
	int	flag;

	nx = x;
	ny = y + 1;
	if (ny <= map->height && cpy[ny][nx] != WALL && cpy[ny][nx] != PASSED)
	{
		flag = move(map, cpy, nx, ny);
		if (flag == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

int	left(t_map *map, char **cpy, int x, int y)
{
	int	nx;
	int	ny;
	int	flag;

	nx = x - 1;
	ny = y;
	if (nx >= 0 && cpy[ny][nx] != WALL && cpy[ny][nx] != PASSED)
	{
		flag = move(map, cpy, nx, ny);
		if (flag == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

int	right(t_map *map, char **cpy, int x, int y)
{
	int	nx;
	int	ny;
	int	flag;

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

int	move(t_map *map, char **cpy, int x, int y)
{
	int	flag;

	if (x < 0 || map->width < x || y < 0
		|| map->height < y || cpy[y][x] == WALL)
		return (FALSE);
	if (cpy[y][x] == EXIT)
		return (TRUE);
	cpy[y][x] = PASSED;
	flag = up(map, cpy, x, y);
	if (flag == TRUE)
		return (TRUE);
	flag = down(map, cpy, x, y);
	if (flag == TRUE)
		return (TRUE);
	flag = left(map, cpy, x, y);
	if (flag == TRUE)
		return (TRUE);
	flag = right(map, cpy, x, y);
	if (flag == TRUE)
		return (TRUE);
	return (FALSE);
}
