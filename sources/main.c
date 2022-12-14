/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:58:19 by kyuzu             #+#    #+#             */
/*   Updated: 2022/12/10 17:28:35 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	count_c(char **array)
{
	int	c_num;
	int	i;
	int	j;

	c_num = 0;
	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] != '\0')
		{
			if (array[i][j] == COLLECTIBLE)
				c_num++;
			j++;
		}
		i++;
	}
	return (c_num);
}

void	init_data(t_data *data)
{
	data->bsize = 70;
	data->window_width = data->map->width * data->bsize;
	data->window_height = data->map->height * data->bsize;
	data->move_count = 0;
	data->x = data->map->start_pos[0] * data->bsize;
	data->y = data->map->start_pos[1] * data->bsize;
	data->c_num = count_c(data->map->array);
	data->c_taken = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Error\nThe program need A map\n");
		return (0);
	}
	data.map = create_map(argv[1]);
	init_data(&data);
	if (make_window(&data) == FALSE)
		free_and_exit(data.map, ARRAY, "Error\nA MLX error has occured\n");
	free_and_exit(data.map, ARRAY, NULL);
	return (0);
}
