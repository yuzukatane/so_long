/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:58:19 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/18 17:16:02 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768


#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0x47885e
#define WHITE_PIXEL 0xFFFFFF
#define GRAY_PIXEL 0xcbd0d3
#define YELLOW_PIXEL 0xe3e548

#define BLUE_PIXEL 0x001e36

//
#define D 100
#define A 97
#define W 119
#define S 115
//要確認

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

/* The x and y coordinates of the rect corresponds to its upper left corner. */

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, BLUE_PIXEL);
		}
		i++;
	}
}


int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img);
	render_rect(&data->img, (t_rect){data->x, data->y, data->block_size_x, data->block_size_y, YELLOW_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == D)/////全部やる
	{
		if (data->map->array[data->y / data->block_size_y][(data->x + data->block_size_x) / data->block_size_x] != WALL)
		{
			data->x += data->block_size_x;
			render(data);
		}
	}
	else if (keysym == A)
	{
		if (data->map->array[data->y / data->block_size_y][(data->x - data->block_size_x) / data->block_size_x] != WALL)
		{
			data->x -= data->block_size_x;
			render(data);
		}
	}
	else if (keysym == S)
	{
		if (data->map->array[(data->y + data->block_size_y) / data->block_size_y][data->x / data->block_size_x] != WALL)
		{
			data->y += data->block_size_y;
			render(data);
		}
	}
	else if (keysym == W)
	{
		if (data->map->array[(data->y - data->block_size_y) / data->block_size_y][data->x / data->block_size_x] != WALL)
		{
			data->y -= data->block_size_y;
			render(data);
		}
	}
	return (0);
}

// int	main(void)
// {
// 	t_data	data;
//
// 	data.mlx_ptr = mlx_init();
// 	if (data.mlx_ptr == NULL)
// 		return (MLX_ERROR);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
// 	if (data.win_ptr == NULL)
// 	{
// 		free(data.win_ptr);
// 		return (MLX_ERROR);
// 	}
//
// 	/* Setup hooks */ 
// 	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
// 			&data.img.line_len, &data.img.endian);
//
// 	mlx_loop_hook(data.mlx_ptr, &render, &data);
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//
// 	mlx_loop(data.mlx_ptr);
//
// 	/* we will exit the loop if there's no window left, and execute this code */
// 	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
//
// 	return (0);
// }

// void make_background(t_data *data)
// {
// 	t_img	back;
//
// 	back.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	back.addr = mlx_get_data_addr(back.mlx_img, &back.bpp,
// 			&back.line_len, &back.endian);
// 	render_background(&back);
//
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, back.mlx_img, 0, 0);
// }



// int	make_window(void)
// {
// 	t_data	data;
// 	char	*relative_path = "./image.xpm";
// 	int		img_width;
// 	int		img_height;
//
// 	//init
// 	data.mlx_ptr = mlx_init();
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
//
// 	make_background(&data);
//
// 	// //image
// 	// data.img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, relative_path, &img_width, &img_height);
// 	// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
// 	// mlx_loop_hook(data.mlx_ptr, &render, &data);
//
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//
// 	mlx_loop(data.mlx_ptr);
// 	// mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
// 	return (0);
// }


int	x_button(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	window(t_data *data)
{
	data->block_size_x = WINDOW_WIDTH / data->map->width;
	data->block_size_y = WINDOW_HEIGHT / data->map->height;
	data->x = data->map->start_pos[0] * data->block_size_x;
	data->y = data->map->start_pos[1] * data->block_size_y;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (FALSE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (FALSE);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	mlx_loop_hook(data->mlx_ptr, &render, data);

	mlx_hook(data->win_ptr, ClientMessage, StructureNotifyMask, &x_button, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	
	
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (TRUE);
}

// void	window(void)
// {
// 	t_data data;
//
// 	// data.x = 0;//
// 	// data.y = 0;//
// 	// data.mlx_ptr = mlx_init();
// 	// // if (data.mlx_ptr == NULL)
// 	// // 	return (MLX_ERROR);		window（）を、void じゃなくてint にしないといけない
// 	// data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
// 	// // if (data.win_ptr == NULL)
// 	// // {
// 	// // 	free(data.win_ptr);
// 	// // 	return (MLX_ERROR);
// 	// // }
// 	// data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
// 	// mlx_loop_hook(data.mlx_ptr, &render, &data);
// 	// mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
// 	// mlx_loop(data.mlx_ptr);
// 	f(&data);
// 	// mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
// 	// mlx_destroy_display(data.mlx_ptr);
// 	// free(data.mlx_ptr);
// }

int	main(int argc, char *argv[])
{
	t_data data;
	if (argc != 2)
	{
		ft_printf("The program need a map\n");
		return (0);
	}

	data.map = create_map(argv[1]);
	
	if (window(&data) == FALSE)
		free_and_exit(data.map, ARRAY, "MLX error");
	free_and_exit(data.map, ARRAY, NULL);
	return (0);
}
