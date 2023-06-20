/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkulket <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:36:16 by tkulket           #+#    #+#             */
/*   Updated: 2023/06/17 18:16:58 by tkulket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libsolong.h"

void ft_playermove(t_sol *sol, int x, int y)
{
//		int x_offset = sol->play.x * sol->box / 1 + sol->box / 4;
//		int y_offset = sol->play.y * sol->box / 1 + sol->box / 2;

	sol->play.x = x ;
	sol->play.y = y ;
	if (sol->map.arr[y][x] != 'E')
		sol->map.arr[y][x] = '0';
//	ft_printf("play co(x, y) = %d, %d\n", sol->play.x, sol->play.y);
//	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0x00ff00, "{P}");
		if(!sol->play.img->ptr)
			return ;
	ft_put_picture(sol, sol->play.img->ptr, sol->play.x * BOX, sol->play.y * BOX);
}

void ft_startwindow(t_sol *sol)
{
        sol->mlx = mlx_init();
		sol->box = BOX;
		ft_printf("boxsize = %d  \n", sol->box);
		ft_printf("map.row = %d ,  map.col  = %d \n", sol->map.row, sol->map.col);
		ft_printf("play.w = %d ,play.h  = %d \n", sol->play.w, sol->play.h);
        sol->h = sol->box * sol->map.row;
        sol->w = sol->box * (sol->map.col - 1);
		sol->play.img = ft_create_picture(sol, sol->play,P_PLAY);
		sol->wall.img = ft_create_picture(sol, sol->wall,P_WALL);
		sol->exit.img = ft_create_picture(sol, sol->exit,P_EXIT);
		sol->coin.img = ft_create_picture(sol, sol->coin,P_COIN);
		sol->sky.img = ft_create_picture(sol, sol->sky,P_SKY);

		sol->win = mlx_new_window(sol->mlx, sol->w, sol->h, "Solong!");
        ft_printf(" window started ......\n");
        ft_printf("block Width = %d, Height = %d \n", sol->w, sol->h);
		ft_printf("play.w = %d ,play.h  = %d \n", sol->play.w, sol->play.h);

		ft_show_pic(sol, &sol->map);
//		ft_printf("P( %d , %d)\n", sol->play.x, sol->play.y);
		ft_playermove(sol, sol->play.x, sol->play.y);

        mlx_key_hook(sol->win, key_hook, sol);
        mlx_loop(sol->mlx);
}


int		key_hook(int keycode, t_sol *sol)
{
		mlx_clear_window(sol->mlx, sol->win);
		if (keycode == KEY_W || keycode == KEY_UP)
			ft_checkup(sol);
		else if (keycode == KEY_A || keycode == KEY_LEFT)
			ft_checkleft(sol);
		else if (keycode == KEY_S || keycode == KEY_DOWN)
			ft_checkdown(sol);
		else if (keycode == KEY_D || keycode == KEY_RIGHT)
			ft_checkright(sol);
        else if (keycode == KEY_ESC)
        {
			ft_destroy_all(sol);
			ft_printf("ESC exit \n");
            exit(0);
        }
		ft_show_pic(sol, &sol->map);
		ft_playermove(sol, sol->play.x, sol->play.y);
		return (0);
}