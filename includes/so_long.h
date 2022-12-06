/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:33:40 by kyuzu             #+#    #+#             */
/*   Updated: 2022/12/06 12:23:44 by kyuzu            ###   ########.fr       */
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

# define D 100
# define A 97
# define W 119
# define S 115

# define TRUE 1
# define FALSE 0

# define P_PATH "./images/crab.xpm"
# define W_PATH "./images/rock.xpm"
# define C_PATH "./images/shell.xpm"
# define E_PATH "./images/home.xpm"
# define EMP_PATH "./images/empty.xpm"

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
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**array;
	int		height;
	int		width;
	int		start_pos[2];
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	player;
	t_img	wall;
	t_img	collectible;
	t_img	_exit;
	t_img	empty;
	t_map	*map;
	int		bsize;
	int		c_num;
	int		c_taken;
	int		x;
	int		y;
	int		move_count;
	int		window_width;
	int		window_height;
}	t_data;

typedef struct s_flag
{
	int	start_flag;
	int	exit_flag;
	int	collective_flag;
}	t_flag;

t_map	*create_map(char *filename);
int		check_map(t_map *map);
int		is_there_a_valid_path(t_map *map, int x, int y);
int		move(t_map *map, char **cpy, int x, int y);
int		make_background(t_data *data);

int	destroy_window(t_data *data);

int	handle_keypress(int keysym, t_data *data);
int	make_window(t_data *data);

void	free_double_ptr(char **double_ptr);
void	free_and_exit(t_map *map, t_free free_flag, char *msg);

#endif
