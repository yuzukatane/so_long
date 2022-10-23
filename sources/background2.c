/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:59:05 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/23 11:03:14 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	put_object(t_data *data, int x, int y)
{
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			if (data->map->array[y][x] == WALL)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->wall.mlx_img, x * data->bsize, y * data->bsize);
			else if (data->map->array[y][x] == COLLECTIBLE)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->\
					collectible.mlx_img, x * data->bsize, y * data->bsize);
			else if (data->map->array[y][x] == EXIT)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->_exit.mlx_img, x * data->bsize, y * data->bsize);
			else
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->empty.mlx_img, x * data->bsize, y * data->bsize);
		}
	}
}

int	make_background(t_data *data)
{
	int		x;
	int		y;

	if (make_images(data) == FALSE)
		return (FALSE);
	x = -1;
	y = -1;
	put_object(data, x, y);
	return (TRUE);
}
