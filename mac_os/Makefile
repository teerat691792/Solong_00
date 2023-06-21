# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkulket <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 10:09:30 by tkulket           #+#    #+#              #
#    Updated: 2023/06/21 21:54:04 by tkulket          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

#LIB		=	-L. -lsolong \
			-Ilibft -Llibft -lft \
			-I../minilibx_linux -L../minilibx_linux -lmlx \
			-L/usr/lib -lXext -lX11 -lm -lz

LIB		=	-L. -lsolong \
			-Ilibft -Llibft -lft \
			-I../minilibx -L../minilibx -lmlx \
			-framework OpenGL -framework AppKit -lz

NAME  = libsolong.a

SRC	= 		ft_solong.c \
			ft_checkmove.c \
			ft_map.c \
			ft_draw.c \
			ft_pic.c \
			ft_flag.c \
			ft_floodfill.c

OBJS := $(SRC:.c=.o)

all: $(NAME)

.c.o:
	gcc $(FLAGS) -c $< -o $(<:.c=.o)
#	gcc $(FLAGS) main.c -L. -lsolong-Ilibft -Llibft -lft \
	-Iminilibx -Lminilibx -lmlx \
	-framework OpenGL -framework AppKit -lz -o solong

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

t:	re
	gcc $(FLAGS) main.c $(LIB) -o solong

man1:
	man ../minilibx_linux/man/man3/mlx.3

man2:
	man ../minilibx_linux/man/man3/mlx_loop.3

man3:
	man ../minilibx_linux/man/man3/mlx_new_image.3

man4:
	man ../minilibx_linux/man/man3/mlx_new_window.3

man5:
	man ../minilibx_linux/man/man3/mlx_pixel_put.3


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
