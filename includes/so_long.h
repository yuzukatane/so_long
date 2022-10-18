/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:33:40 by kyuzu             #+#    #+#             */
/*   Updated: 2022/10/18 16:26:00 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "../libraries/libft/libft.h"
# include "../libraries/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define START 'P'
# define PASSED 'X'

# define TRUE 1
# define FALSE 0

typedef enum e_free
{
	NOTHING,
	MAP_PTR,
	ARRAY
}	t_free;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**array;
	int		height;
	int		width;
	int		start_pos[2];
	int		exit_pos[2];
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_map	*map;
	int		block_size_x;
	int		block_size_y;
	// int		cur_img;
	int		x;
	int		y;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_flag
{
	int	start_flag;
	int	exit_flag;
	int	collective_flag;
}	t_flag;

t_map	*create_map(char *filename);

int		check_map(t_map *map);
int	is_there_a_valid_path(t_map *map, int x, int y);

void	free_double_ptr(char **double_ptr);
void	free_and_exit(t_map *map, t_free free_flag, char *msg);


#endif
