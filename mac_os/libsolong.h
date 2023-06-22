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

# include <math.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define MAX_HEIGHT 1280
# define MAX_WIDTH 2560
# define CLK_CLOSE 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_UP 126
# define BOX 64

/*

# define MAX_HEIGHT 1280
# define MAX_WIDTH 2560
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define BOX 64

*/

# define P_PLAY "./pic_xpm/bird_mod_64.xpm"
# define P_SKY "./pic_xpm/blue_mod_64.xpm"
# define P_WALL "./pic_xpm/block_mod_64.xpm"
# define P_COIN "./pic_xpm/coin_mod_64.xpm"
# define P_EXIT "./pic_xpm/exit_mod_64.xpm"

// [y][x]
typedef struct s_ber
{
	int		**arr;
	int		**tmp;
	char	*str;
	int		len;
	int		row;
	int		col;
}	t_ber;

typedef struct s_image
{
	void	*ptr;
	char	*pixel;
	int		bpp;
	int		ls;
	int		endian;
}	t_image;

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

//ft_solong.c
void	ft_playermove(t_sol *sol, int x, int y);
void	ft_startwindow(t_sol *sol);
int		ft_key_hook(int keycode, t_sol *sol);
int		ft_clickclose(t_sol *sol);

//ft_draw.c
void	ft_draw_pixel(int width, int height, t_sol *sol);
void	ft_draw_grid(int box, int width, int height, t_sol *sol);
void	ft_show_str(int box, t_sol *sol, t_ber *map);

// ft_flag.c
int		ft_noborder_up_dw(t_sol *sol);
int		ft_noborder_lf_rg(t_sol *sol);
int		ft_stranger(t_sol *sol);
int		ft_checkflag(t_sol *sol);
int		ft_findartifact(char *str, int c);

// ft_map.c
void	ft_collectmap(int fd, t_sol *sol);
int		**ft_mallocmap(t_ber *map);
int		**ft_assignmap(int **arr, t_ber *map);
void	ft_readmap(int **arr, t_ber *map);
void	ft_freemap(int	**arr, t_ber *map);
//void	ft_readber(int fd);

//	checkmove
int		ft_checkup(t_sol *sol);
int		ft_checkdown(t_sol *sol);
int		ft_checkright(t_sol *sol);
int		ft_checkleft(t_sol *sol);

//ft_floodfill.c
int		ft_validpath(t_sol *sol);
int		ft_findpos(t_sol *sol, int value, int *flag);
void	ft_dps(int **arr, int x, int y, int *valid);
int		ft_rev_findpos(t_sol *sol, int value);
void	ft_rev_dps(int **arr, int x, int y, int *count);

//ft_pic.c
void	ft_init_pic(t_data *data);
t_image	*ft_create_picture(t_sol *sol, t_data obj, char *path);
void	ft_destroy_all(t_sol *sol);
void	ft_show_pic(t_sol *sol, t_ber *map);
void	ft_put_picture(t_sol *sol, void *ptr, int x, int y);

#endif