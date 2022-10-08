/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:19:06 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/08 15:21:49 by kyuzu            ###   ########.fr       */
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