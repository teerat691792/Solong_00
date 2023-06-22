/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkulket <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:58:00 by tkulket           #+#    #+#             */
/*   Updated: 2023/06/22 21:58:03 by tkulket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsolong.h"

void	ft_init_pic(t_data *data)
{
	data->img = malloc(sizeof(t_image));
	data->img->ptr = NULL;
	data->img->pixel = NULL;
	data->img->bpp = 0;
	data->img->ls = 0;
	data->img->endian = 0;
	data->path = NULL;
	data->move = 0;
}

t_image	*ft_create_picture(t_sol *sol, t_data obj, char *path)
{
	obj.img = malloc(sizeof(t_image));
	obj.img->ptr = mlx_xpm_file_to_image(sol->mlx, path, &obj.w, &obj.h);
	if (!path)
		ft_printf("NO >>>>>PATH  \n");
	if (!obj.img->ptr)
		ft_printf("NO pic  %s \n", path);
	obj.img->pixel = mlx_get_data_addr(obj.img->ptr \
		, &obj.img->bpp, &obj.img->ls, &obj.img->endian);
	return (obj.img);
}

void	ft_destroy_all(t_sol *sol)
{
	mlx_destroy_image(sol->mlx, sol->play.img->ptr);
	mlx_destroy_image(sol->mlx, sol->wall.img->ptr);
	mlx_destroy_image(sol->mlx, sol->sky.img->ptr);
	mlx_destroy_image(sol->mlx, sol->coin.img->ptr);
	mlx_destroy_image(sol->mlx, sol->exit.img->ptr);
	mlx_destroy_window(sol->mlx, sol->win);
}

void	ft_show_pic(t_sol *sol, t_ber *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->row)
	{
		while (x < map->col)
		{
			ft_put_picture(sol, sol->sky.img->ptr, x * BOX, y * BOX);
			if (map->arr[y][x] == '1')
				ft_put_picture(sol, sol->wall.img->ptr, x * BOX, y * BOX);
			else if (map->arr[y][x] == 'E')
				ft_put_picture(sol, sol->exit.img->ptr, x * BOX, y * BOX);
			else if (map->arr[y][x] == 'C')
				ft_put_picture(sol, sol->coin.img->ptr, x * BOX, y * BOX);
			else if (map->arr[y][x] == 'P')
				ft_playermove(sol, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	ft_put_picture(t_sol *sol, void *ptr, int x, int y)
{
	mlx_put_image_to_window(sol->mlx, sol->win, ptr, x, y);
}
