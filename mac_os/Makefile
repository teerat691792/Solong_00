# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkulket <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 10:09:30 by tkulket           #+#    #+#              #
#    Updated: 2023/06/17 15:08:13 by tkulket          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = libsolong.a

SRC		=	ft_solong.c

OBJS :=$(SRC:.c=.o)

all = $(NAME)

.c.o:
	gcc $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

t:
	gcc $(FLAGS) solong.c -Ilibft -Llibft -lft -Iminilibx -Lminilibx -lmlx -framework OpenGL -framework AppKit -lz 

m:
	make -C ./minilibx_opengl re

man1:
	man minilibx/man/man3/mlx.3

man2:
	man minilibx/man/man3/mlx_loop.3

man3:
	man minilibx/man/man3/mlx_new_image.3

man4:
	man minilibx/man/man3/mlx_new_window.3

man5:
	man minilibx/man/man3/mlx_pixel_put.3
	

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
