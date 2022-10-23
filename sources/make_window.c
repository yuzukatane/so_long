/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:02:45 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/23 11:39:17 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	destroy_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

void	destroy_images(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->player.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->wall.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->collectible.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->_exit.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->empty.mlx_img);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->player.mlx_img, data->x, data->y);
	return (0);
}

void	loop(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, ClientMessage, StructureNotifyMask,
		&destroy_window, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop(data->mlx_ptr);
}

int	make_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (FALSE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window_width,
			data->window_height, "so_long");
	if (data->win_ptr == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (FALSE);
	}
	if (make_background(data) == FALSE)
	{
		destroy_images(data);
		destroy_window(data);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (FALSE);
	}
	loop(data);
	destroy_images(data);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (TRUE);
}
