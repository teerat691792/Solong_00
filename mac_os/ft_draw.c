

#include "libsolong.h"


void ft_draw_pixel(int width, int height, t_sol *sol)
{
        int     i = 0;
        int		j = 0;

        while(i < width)
        {
                while(j < height)
                {
                        mlx_pixel_put(sol->mlx, sol->win, i , j, 0xffffff);
                        j++;
                }
                j = 0;
                i++;
        }
}

void ft_draw_grid(int box ,int width , int height, t_sol *sol)
{
	int x = 0;
	int y = 0;
	int tmp = 0;

	while(x < sol->w)
    {
		while(y < sol->h)
		{
			if  (y % height == 0 )
			{
				while(tmp < sol->w || tmp < box)
				{
					mlx_pixel_put(sol->mlx, sol->win, tmp + x , y, 0xff00ff);
					tmp++;
				}
				tmp = 0;
			}
			else
				mlx_pixel_put(sol->mlx, sol->win, x , y, 0x00bbbb);
			y++;
		}
	y = 0;
	x += width;
	}
}

void ft_show_str(int box, t_sol *sol, t_ber *map)
{
	int x;
	int y;
//	int x_pic;
//	int y_pic;
	int x_offset;
	int y_offset;

	x = 0;
	y = 0;
	while (y < map->row )
	{
		while (x < map->col)
		{
			x_offset = x * box / 1 + box / 4;
			y_offset = y * box / 1 + box / 2;
//			x_pic = x * box;
//			y_pic = y * box;
//			ft_printf("(%c) x = %d , y = %d \n",map->arr[y][x], x,y);
mlx_string_put(sol->mlx, sol->win, x_offset+5, y_offset+5, 0x666666, " 0");
//mlx_put_image_to_window(sol->mlx, sol->win, sol->sky.img->ptr, x_offset, y_offset);
			if( map->arr[y][x] == '1')
			{
	mlx_string_put(sol->mlx, sol->win, x_offset ,  y_offset , 0xffffff, "[1]");
//	mlx_put_image_to_window(sol->mlx, sol->win, sol->wall.img->ptr, x_pic, y_pic);

			}
//			else if( map->arr[y][x] == 'P' && !sol->play.x && !sol->play.y)
			else if( map->arr[y][x] == 'P')
			{
				ft_printf("get play x,y");
				sol->play.x = x;
				sol->play.y = y;
				map->arr[y][x] = '0';
//	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0x00ff00, "{P}");
//	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0x666666, " 0");
			}
			else if( map->arr[y][x] == 'E')
			{
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0xff0066, "[E]");
//	mlx_put_image_to_window(sol->mlx, sol->win, sol->exit.img->ptr, x_pic, y_pic);

			}
			else if( map->arr[y][x] == 'C')
			{
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0xffff00, "(C)");
//	mlx_put_image_to_window(sol->mlx, sol->win, sol->coin.img->ptr, x_pic, y_pic);
			}
//			if( map->arr[y][x] == '0')
//			{
//	mlx_string_put(sol->mlx, sol->win, x_offset,y_offset,0x666666, " 0");
//			}
			x++;
		}
		x = 0;
		y++;
	}
}

