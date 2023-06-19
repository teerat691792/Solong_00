/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsolong.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkulket <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:56:29 by tkulket           #+#    #+#             */
/*   Updated: 2023/06/17 18:17:25 by tkulket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOLONG_H
# define LIBSOLONG_H

#include <math.h>

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_UP 126
# define KEY_UP 126
# define KEY_UP 126
# define P_PLAY "./pic/bird_64.png"
# define P_SKY "./pic/sky_64.png"
# define P_WALL "./pic/wall_64.png"
# define P_COIN "./pic/coin_64.png"
# define P_EXIT "./pic/exit_64.png"


typedef struct s_ber
{
	int				**arr; //[y][x]
	int				**tmp; //[y][x]
	char			*str;
	int 			len;
	int				row;
	int				col;
}	t_ber;

typedef struct	s_image
{
	void      *ptr;
//	t_vector  size;
	char      *pixel;
	int       bpp;
	int       ls;
	int       endian;
}   t_image;

typedef struct s_data
{
	t_image	*img;
	char	*path;
	int		move;
	int		count;
	int		x;
	int		y;
	int		w;
	int		h;
}	t_data;

typedef struct s_sol
{
	void	*mlx;
	void	*win;
	int		box;
	int		w;
	int		h;
	t_ber	map;
	t_data	play;
	t_data	wall;
	t_data	coin;
	t_data	exit;
	t_data	sky;
}	t_sol;



#endif
