/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:45:42 by kyuzu             #+#    #+#             */
/*   Updated: 2022/11/30 15:42:22 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	d(t_data *data)
{
	if (data->map->array[data->y / data->bsize]
		[(data->x + data->bsize) / data->bsize] != WALL)
	{
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->_exit.mlx_img, data->x, data->y);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->empty.mlx_img, data->x, data->y);
		data->x += data->bsize;
		ft_printf("%d\n", ++data->move_count);
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == COLLECTIBLE)
				data->c_taken++;
		else if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
		{
			if (data->c_taken == data->c_num)
				destroy_window(data);
		}
	}
}

void	a(t_data *data)
{
	if (data->map->array[data->y / data->bsize]
		[(data->x - data->bsize) / data->bsize] != WALL)
	{
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->_exit.mlx_img, data->x, data->y);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->empty.mlx_img, data->x, data->y);
		data->x -= data->bsize;
		ft_printf("%d\n", ++data->move_count);
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == COLLECTIBLE)
				data->c_taken++;
		else if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
		{
			if (data->c_taken == data->c_num)
				destroy_window(data);
		}
	}
}

void	s(t_data *data)
{
	if (data->map->array[(data->y + data->bsize) / data->bsize]
		[data->x / data->bsize] != WALL)
	{
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->_exit.mlx_img, data->x, data->y);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->empty.mlx_img, data->x, data->y);
		data->y += data->bsize;
		ft_printf("%d\n", ++data->move_count);
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == COLLECTIBLE)
				data->c_taken++;
		else if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
		{
			if (data->c_taken == data->c_num)
				destroy_window(data);
		}
	}
}

void	w(t_data *data)
{
	if (data->map->array[(data->y - data->bsize) / data->bsize]
		[data->x / data->bsize] != WALL)
	{
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->_exit.mlx_img, data->x, data->y);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->empty.mlx_img, data->x, data->y);
		data->y -= data->bsize;
		ft_printf("%d\n", ++data->move_count);
		if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == COLLECTIBLE)
				data->c_taken++;
		else if (data->map->array[data->y / data->bsize]
			[data->x / data->bsize] == EXIT)
		{
			if (data->c_taken == data->c_num)
				destroy_window(data);
		}
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == D)
		d(data);
	else if (keysym == A)
		a(data);
	else if (keysym == S)
		s(data);
	else if (keysym == W)
		w(data);
	return (0);
}
