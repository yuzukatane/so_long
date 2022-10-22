/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:46:28 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/22 19:19:31 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	render_rect(t_data *data, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->block_size_y)
	{
		x = 0;
		while (x < data->block_size_x)
		{
			img_pix_put(img, x, y, GRAY_PIXEL);
			x++;
		}
		y++;
	}
	return (0);
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
	data->empty.mlx_img = mlx_new_image(data->mlx_ptr,
			data->block_size_x, data->block_size_y);
	data->empty.addr = mlx_get_data_addr(data->empty.mlx_img, &data->empty.bpp,
			&data->empty.line_len, &data->empty.endian);
	render_rect(data, &data->empty);
	if (data->player.mlx_img == NULL || data->wall.mlx_img == NULL
		|| data->collectible.mlx_img == NULL || data->_exit.mlx_img == NULL
		|| data->empty.mlx_img == NULL)
		return (FALSE);
	return (TRUE);
}

int	make_background(t_data *data)
{
	int		x;
	int		y;	

	if (make_images(data) == FALSE)
		return (FALSE);
	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			if (data->map->array[y][x] == WALL)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->wall.mlx_img, x * data->block_size_x,
					y * data->block_size_y);
			else if (data->map->array[y][x] == COLLECTIBLE)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->collectible.mlx_img, x * data->block_size_x,
					y * data->block_size_y);
			else if (data->map->array[y][x] == EXIT)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->_exit.mlx_img, x * data->block_size_x,
					y * data->block_size_y);
			else
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->empty.mlx_img, x * data->block_size_x,
					y * data->block_size_y);
		}
	}
	return (TRUE);
}
