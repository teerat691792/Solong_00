


#ifndef SOLONG_H
# define SOLONG_H

#include <math.h>


# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363


typedef struct s_ber
{
	int				**arr; //[y][x]
	char			*str;
	int 			len;
	int				row;
	int				col;
}	t_ber;


typedef struct s_data
{
	void	*img;
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
}	t_sol;



#endif
