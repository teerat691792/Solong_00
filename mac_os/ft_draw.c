

#include "libsolong.h"


void	ft_draw_pixel(int width, int height, t_sol *sol)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < width)
	{
		while (j < height)
		{
			mlx_pixel_put(sol->mlx, sol->win, i, j, 0xffffff);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_draw_grid(int box, int width, int height, t_sol *sol)
{
	int	x;
	int	y;
	int	tmp;

	x = 0;
	y = 0;
	tmp = 0;
	while (x < sol->w)
	{
		while (y < sol->h)
		{
			if (y % height == 0)
			{
				while (tmp < sol->w || tmp < box)
				{
					mlx_pixel_put(sol->mlx, sol->win, tmp + x, y, 0xff00ff);
					tmp++;
				}
				tmp = 0;
			}
			else
				mlx_pixel_put(sol->mlx, sol->win, x, y, 0x00bbbb);
			y++;
		}
	y = 0;
	x += width;
	}
}

void	ft_show_str(int box, t_sol *sol, t_ber *map)
{
	int	x;
	int	y;
	int	x_offset;
	int	y_offset;

	x = 0;
	y = 0;
	while (y < map->row)
	{
		while (x < map->col)
		{
			x_offset = x * box / 1 + box / 4;
			y_offset = y * box / 1 + box / 2;
			mlx_string_put (sol->mlx, sol->win, x_offset + 5, y_offset + 5, 0x666666, " 0");
			if (map->arr[y][x] == '1')
				mlx_string_put (sol->mlx, sol->win, x_offset, y_offset, 0xffffff, "[1]");
			else if (map->arr[y][x] == 'P')
			{
				ft_printf("get play x,y");
				sol->play.x = x;
				sol->play.y = y;
				map->arr[y][x] = '0';
			}
			else if (map->arr[y][x] == 'E')
				mlx_string_put (sol->mlx, sol->win, x_offset, y_offset, 0xff0066, "[E]");
			else if (map->arr[y][x] == 'C')
				mlx_string_put (sol->mlx, sol->win, x_offset, y_offset, 0xffff00, "(C)");
			x++;
		}
		x = 0;
		y++;
	}
}
