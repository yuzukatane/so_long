NAME = so_long
# CFLAGS = -Wall -Wextra -Werror
CFLAGS += $(INCLUDES)
CC = gcc
LIBFT_PATH = ./libraries/libft
MLX_PATH = ./libraries/minilibx-linux
X11_PATH = /usr/X11/include/../lib
INCLUDES = -I includes -I/usr/X11/include
LIBS_PATH = -L$(LIBFT_PATH) -L$(MLX_PATH) -L$(X11_PATH)
LIBS = -lft -lmlx_Darwin -lXext -lX11 -framework OpenGL -framework AppKit
FILES = main.c create_map.c check_map1.c check_map2.c free.c background.c
SRCS = $(addprefix sources/,$(FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	make -C $(MLX_PATH)

	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS_PATH) $(LIBS)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_PATH)
	make clean -C $(MLX_PATH)

fclean:
	rm -f $(OBJS) $(NAME)
	make fclean -C $(LIBFT_PATH)
	make clean -C $(MLX_PATH)

re: fclean all


.PHONY: all clean fclean re
