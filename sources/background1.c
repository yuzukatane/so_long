/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:00:14 by kyuzu             #+#    #+#             */
/*   Updated: 2022/12/06 12:16:32 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_images(t_data *data)
{
	if (data->player.mlx_img == NULL || data->wall.mlx_img == NULL
		|| data->collectible.mlx_img == NULL || data->_exit.mlx_img == NULL
		|| data->empty.mlx_img == NULL)
		return (FALSE);
	return (TRUE);
}

int	make_images(t_data *data)
{
	data->player.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, P_PATH,
			&data->player.width, &data->player.height);
	data->player.addr = mlx_get_data_addr(data->player.mlx_img,
			&data->player.bpp, &data->player.line_len, &data->player.endian);
	data->wall.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, W_PATH,
			&data->wall.width, &data->wall.height);
	data->wall.addr = mlx_get_data_addr(data->wall.mlx_img, &data->wall.bpp,
			&data->wall.line_len, &data->wall.endian);
	data->collectible.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, C_PATH,
			&data->collectible.width, &data->collectible.height);
	data->collectible.addr = mlx_get_data_addr(data->collectible.mlx_img,
			&data->collectible.bpp,
			&data->collectible.line_len, &data->collectible.endian);
	data->_exit.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, E_PATH,
			&data->_exit.width, &data->_exit.height);
	data->_exit.addr = mlx_get_data_addr(data->_exit.mlx_img, &data->_exit.bpp,
			&data->_exit.line_len, &data->_exit.endian);
	data->empty.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, EMP_PATH,
			&data->empty.width, &data->empty.height);
	data->empty.addr = mlx_get_data_addr(data->empty.mlx_img, &data->empty.bpp,
			&data->empty.line_len, &data->empty.endian);
	return (check_images(data));
}

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
