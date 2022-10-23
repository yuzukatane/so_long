/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:19:06 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/23 11:47:59 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_double_ptr(char **double_ptr)
{
	int	i;

	i = 0;
	while (double_ptr[i] != NULL)
	{
		free(double_ptr[i]);
		i++;
	}
	free(double_ptr);
}

void	free_and_exit(t_map *map, t_free free_flag, char *msg)
{
	if (free_flag >= ARRAY)
		free_double_ptr(map->array);
	if (free_flag >= MAP_PTR)
		free(map);
	if (msg != NULL)
		ft_printf("%s\n", msg);
	exit(0);
}
