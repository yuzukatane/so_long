/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:58:19 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/22 18:16:40 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == D)
	{
		if (data->map->array[data->y / data->block_size_y][(data->x + data->block_size_x) / data->block_size_x] != WALL)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->empty.mlx_img, data->x, data->y);
			data->x += data->block_size_x;
			ft_printf("%d\n", ++data->move_count);
			if (data->map->array[data->y / data->block_size_y][data->x / data->block_size_x] == EXIT)
				destroy_window(data);
		}
	}
	else if (keysym == A)
	{
		if (data->map->array[data->y / data->block_size_y][(data->x - data->block_size_x) / data->block_size_x] != WALL)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->empty.mlx_img, data->x, data->y);
			data->x -= data->block_size_x;
			ft_printf("%d\n", ++data->move_count);
			if (data->map->array[data->y / data->block_size_y][data->x / data->block_size_x] == EXIT)
				destroy_window(data);
		}
	}
	else if (keysym == S)
	{
		if (data->map->array[(data->y + data->block_size_y) / data->block_size_y][data->x / data->block_size_x] != WALL)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->empty.mlx_img, data->x, data->y);
			data->y += data->block_size_y;
			ft_printf("%d\n", ++data->move_count);
			if (data->map->array[data->y / data->block_size_y][data->x / data->block_size_x] == EXIT)
				destroy_window(data);
		}
	}
	else if (keysym == W)
	{
		if (data->map->array[(data->y - data->block_size_y) / data->block_size_y][data->x / data->block_size_x] != WALL)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->empty.mlx_img, data->x, data->y);
			data->y -= data->block_size_y;
			ft_printf("%d\n", ++data->move_count);
			if (data->map->array[data->y / data->block_size_y][data->x / data->block_size_x] == EXIT)
				destroy_window(data);
		}
	}
	return (0);
}



int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.mlx_img, data->x, data->y);
	return (0);
}

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
int	window(t_data *data)
{
	data->move_count = 0;
	data->x = data->map->start_pos[0] * data->block_size_x;
	data->y = data->map->start_pos[1] * data->block_size_y;
	
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (FALSE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window_width, data->window_height, "so_long");
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

	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, ClientMessage, StructureNotifyMask, &destroy_window, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop(data->mlx_ptr);
	
	destroy_images(data);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_data data;
	if (argc != 2)
	{
		ft_printf("The program need a map\n");
		return (0);
	}
	data.map = create_map(argv[1]);
	
	data.block_size_x = 70;
	data.block_size_y = 70;
	
	data.window_width = data.map->width * data.block_size_x;
	data.window_height = data.map->height * data.block_size_y;
	
	if (window(&data) == FALSE)
		free_and_exit(data.map, ARRAY, "MLX error");
	free_and_exit(data.map, ARRAY, NULL);
	return (0);
}
