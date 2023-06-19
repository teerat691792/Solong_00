/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkulket <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:51:38 by tkulket           #+#    #+#             */
/*   Updated: 2023/06/12 17:50:26 by tkulket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/libft.h"
#include "libsolong.h"

void	ft_draw_pixel(void *mlx, void *win, int x, int y);


int	key_hook(int keycode, t_program *ptr)
{
	(void)keycode;
	printf("Hello from key_hook!\n");
	printf("%d\n",keycode);
	if(keycode == KEY_W | keycode == KEY_DOWN) 
	{
		mlx_clear_window(ptr->mlx, ptr->win);
		ptr->y += 10;
	}
	else if(keycode == KEY_A | keycode == KEY_LEFT)
	{
		mlx_clear_window(ptr->mlx, ptr->win);
		if (ptr->x > 0)
			ptr->x -= 10;
	}
	else if(keycode == KEY_S | keycode == KEY_UP)
	{
		mlx_clear_window(ptr->mlx, ptr->win);
		if (ptr->y > 0)
			ptr->y -= 10;
	}
	else if(keycode == KEY_D | keycode == KEY_RIGHT)
	{
		mlx_clear_window(ptr->mlx, ptr->win);
		ptr->x += 10;
	}
	if (keycode == KEY_ESC) //ESC
	{
		mlx_clear_window(ptr->mlx, ptr->win);
		mlx_destroy_window (ptr->mlx, ptr->win );
		exit (0);
	}
		ft_draw_pixel(ptr->mlx, ptr->win, ptr->x, ptr->y);
//		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, ptr->width, ptr->height);
	return (0);
}


int main(void)
{
//	char	*path = "./picture/bird_64.png";
	t_program	ptr;
	double	tet;
	

	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, 500, 500, "mlx 42");
	ptr.x = 90;
	ptr.y = 90;
	ft_draw_pixel(ptr.mlx, ptr.win, ptr.x, ptr.x);
//	mlx_new_image(ptr.mlx, 100, 100);
//	ptr.img = mlx_png_file_to_image(ptr.mlx, path, &ptr.width, &ptr.height);
//	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 100, 100);
	ft_printf("asdasdasd\n");
	tet = pow(2,2);
	ft_printf("tet %d\n",(int)tet);
	mlx_key_hook(ptr.win, key_hook, &ptr);
	mlx_loop(ptr.mlx);

	return (0);
}

void	ft_draw_pixel(void *mlx, void *win, int x, int y)
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
