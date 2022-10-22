/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:58:19 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/22 22:10:22 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_data(t_data *data)
{
	data->bsize = 70;
	data->window_width = data->map->width * data->bsize;
	data->window_height = data->map->height * data->bsize;
	data->move_count = 0;
	data->x = data->map->start_pos[0] * data->bsize;
	data->y = data->map->start_pos[1] * data->bsize;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("The program need a map\n");
		return (0);
	}
	data.map = create_map(argv[1]);
	init_data(&data);
	if (make_window(&data) == FALSE)
		free_and_exit(data.map, ARRAY, "MLX error");
	free_and_exit(data.map, ARRAY, NULL);
	return (0);
}
