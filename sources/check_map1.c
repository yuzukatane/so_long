/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:42:08 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/23 11:05:46 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_rect_big_enough(t_map *map)
{
	int	x;
	int	y;

	x = ft_strlen(map->array[0]);
	y = 0;
	while (map->array[y + 1] != NULL)
	{
		y++;
		if (x != (int)ft_strlen(map->array[y]))
			return (FALSE);
	}
	map->height = y;
	if (map->height < 2)
		return (FALSE);
	map->width = x - 1;
	return (TRUE);
}

int	is_surrounded(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y == 0 || y == map->height)
	{
		x = 0;
		while (map->array[y][x] != '\0')
		{
			if (map->array[y][x] != WALL)
				return (FALSE);
			x++;
		}
		y += map->height;
	}
	x = 1;
	while (x < map->height)
	{
		if (!(map->array[x][0] == WALL && map->array[x][map->width] == WALL))
			return (FALSE);
		x++;
	}
	return (TRUE);
}

int	check_letters(t_map *map, t_flag *flag, int x, int y)
{
	while (++y <= map->height)
	{
		x = -1;
		while (++x <= map->width)
		{
			if (map->array[y][x] == START)
			{
				map->start_pos[0] = x;
				map->start_pos[1] = y;
				flag->start_flag++;
			}
			else if (map->array[y][x] == EXIT)
				flag->exit_flag++;
			else if (map->array[y][x] == COLLECTIBLE)
			{
				if (is_there_a_valid_path(map, x, y) == FALSE)
					return (FALSE);
				flag->collective_flag++;
			}
			else if (map->array[y][x] != WALL && map->array[y][x] != EMPTY)
				return (FALSE);
		}
	}
	return (TRUE);
}

int	is_good_letter(t_map *map)
{
	t_flag	flag;
	int		x;
	int		y;

	flag = (t_flag){.start_flag = 0, .exit_flag = 0, .collective_flag = 0};
	x = -1;
	y = -1;
	if (check_letters(map, &flag, x, y) == FALSE)
		return (FALSE);
	if (flag.start_flag != 1
		|| flag.exit_flag != 1
		|| flag.collective_flag == 0)
		return (FALSE);
	return (TRUE);
}

int	check_map(t_map *map)
{
	if (is_rect_big_enough(map) == FALSE
		|| is_surrounded(map) == FALSE
		|| is_good_letter(map) == FALSE
		|| is_there_a_valid_path
		(map, map->start_pos[0], map->start_pos[1]) == FALSE
		|| map->width == map->height)
		return (FALSE);
	return (TRUE);
}
