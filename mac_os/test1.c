/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkulket <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:46:29 by tkulket           #+#    #+#             */
/*   Updated: 2023/06/17 12:23:32 by tkulket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/libft.h"
#include "libsolong.h"

void	ft_draw_background(void *mlx, void *win, int width, int height);

int	key_hook(int keycode, t_program *ptr)
{
	printf("keycode = %d\n",keycode);
	mlx_clear_window(ptr->mlx, ptr->win);
	if (keycode == KEY_W | keycode == KEY_UP)
	{
		if (ptr->player.y - ptr->player.width > 0)
			ptr->player.y -= ptr->player.height;
	}
	else if (keycode == KEY_A | keycode == KEY_LEFT)
	{
		if (ptr->player.x - ptr->player.width > 0)
			ptr->player.x -= ptr->player.width;
	}
	else if (keycode == KEY_S | keycode == KEY_DOWN)
	{
		if (ptr->player.y + ptr->player.height < ptr->height - ptr->player.height)
			ptr->player.y += ptr->player.height;
	}
    else if (keycode == KEY_D | keycode == KEY_RIGHT)
	{
		if (ptr->player.x + ptr->player.width < ptr->width - ptr->player.width)
			ptr->player.x += ptr->player.width;
	}
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window (ptr->mlx, ptr->win );
		exit (0);
	}
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->player.img, ptr->player.x, ptr->player.y);
	return (0);
}


int main(void)
{
	char	*path1 = "./picture/bird_64.png";
	char	*path2 = "./picture/sky_64.png";
	t_program	ptr;
//	double	tet;


	ptr.mlx = mlx_init();
	ptr.player.img = mlx_png_file_to_image(ptr.mlx, path1, &ptr.player.width, &ptr.player.height);
	ptr.bg.img = mlx_png_file_to_image(ptr.mlx, path2, &ptr.bg.width, &ptr.bg.height);
	ft_printf("asdasdasd\n");
	ptr.player.x = ptr.player.width;
	ptr.player.y = ptr.player.height;
	ptr.width = 10 * ptr.player.width;
	ptr.height = 10 * ptr.player.height;
	ptr.win = mlx_new_window(ptr.mlx, ptr.width, ptr.height, "mlx 42");
//	ft_printf("X = %d, Y = %d, W = %d, H %d ,win %d, %d \n",ptr.player.x, ptr.player.y,ptr.player.width,ptr.player.height,ptr.width,ptr.height);
//	tet = pow(2,2);
//	ft_printf("tet %d\n",(int)tet);
	ptr.pic = mlx_new_image(ptr.mlx, ptr.width, ptr.height);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.bg.img, ptr.width, ptr.height);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.player.img, ptr.player.x, ptr.player.y);
	mlx_key_hook(ptr.win, key_hook, &ptr);
	mlx_loop(ptr.mlx);

	return (0);
}

void	ft_draw_pixel(void *mlx, void *win, int x, int y )
{
	int i = 0;
	int j = 0;

	while (i < 40)
	{
		while (j < 40)
		{
			mlx_pixel_put(mlx, win, i + x, j + y, 0xFFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_draw_background(void *mlx, void *win, int width, int height)
{
	int i = 0;
	int j = 0;

	while (i < width)
	{
		while (j < height)
		{
			mlx_pixel_put(mlx, win, i, j, 0xFFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
	
}
