
/* **********************************************************************  */

#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "solong.h"

//mlx
int		ft_findartifact(char *str,int c);
void	ft_startwindow(t_sol *sol);
int     key_hook(int keycode, t_sol *sol);
void	ft_draw_pixel(int width, int height, t_sol  *sol);
void	ft_draw_grid(int box, int width , int height, t_sol *sol);
void	ft_show_str(int box, t_sol *sol, t_ber *map);
void	ft_playermove(t_sol *sol);


// .ber to **arr
void	ft_readber(int fd);
void	ft_collectmap(int fd, t_sol *sol);
int	**ft_mallocmap(t_ber *map);
void	ft_freemap(int	**arr, t_ber *map);
int		**ft_assignmap(int **arr, t_ber *map);
void	ft_readmap(t_ber *map);

//	checkmove
int		ft_checkup(t_sol *sol);
int		ft_checkdown(t_sol *sol);
int		ft_checkright(t_sol *sol);
int		ft_checkleft(t_sol *sol);

int	main(int argc, char **argv)
{
	int			fd;
	t_sol		sol;

	if (argc != 2)
	{
		ft_printf("input incorrect \n");
		return (1);
	}
	else
	{
		ft_printf("initializing..... \n");
		fd = open(argv[1], O_APPEND | O_RDONLY);
		if (fd < 0)
		{
			ft_printf("open ERROR \n");
			return (2);
		}
//		ft_readber(fd);
		ft_collectmap(fd, &sol);
		close(fd);
			ft_printf("col 	= %d\n",sol.map.col);
			ft_printf("row 	= %d\n",sol.map.row);
			ft_printf("len 	= %d\n",sol.map.len);
		sol.play.count = ft_findartifact(sol.map.str, 'P');
		sol.coin.count = ft_findartifact(sol.map.str, 'C');
		sol.exit.count = ft_findartifact(sol.map.str, 'E');
		sol.play.move = 0;
			ft_printf("play = %d\n",sol.play.count);
			ft_printf("coin = %d\n",sol.coin.count);
			ft_printf("exit = %d\n",sol.exit.count);
		sol.map.arr = ft_mallocmap(&sol.map);
		sol.map.arr = ft_assignmap(sol.map.arr, &sol.map);
		
		ft_startwindow(&sol);
		ft_freemap(sol.map.arr, &sol.map);
		free(sol.map.str);
		return (0);
	}
}


int		ft_findartifact(char *str,int c)
{
	int count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void ft_startwindow(t_sol *sol)
{

        sol->mlx = mlx_init();
        sol->box = 40;
        sol->h = sol->box * sol->map.row;
        sol->w = sol->box * (sol->map.col - 1);

        sol->win = mlx_new_window(sol->mlx, sol->w, sol->h, "Solong!");
        ft_printf(" window started ......\n");
        ft_printf("block Width = %d, Height = %d \n", sol->w, sol->h);
		ft_readmap(&sol->map);

//		ft_draw_grid(sol->box, sol->box, sol->box, sol);
		ft_show_str(sol->box, sol, &sol->map);
		ft_playermove(sol);
        mlx_key_hook(sol->win, key_hook, sol);
        mlx_loop(sol->mlx);

}

int		ft_checkleft(t_sol *sol)
{
	if (sol->map.arr[sol->play.y][sol->play.x - 1] == 'E')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			exit(1);
		}
	}
	if (sol->map.arr[sol->play.y][sol->play.x - 1] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y][sol->play.x - 1] = '0';
	}
	if (sol->map.arr[sol->play.y][sol->play.x - 1] == '1')
		return(0);
	
	sol->play.move++;
	return (1);
}


int		ft_checkup(t_sol *sol)
{
	if (sol->map.arr[sol->play.y - 1][sol->play.x] == 'E')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			exit(1);
		}
	}
	if (sol->map.arr[sol->play.y - 1][sol->play.x] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y - 1][sol->play.x] = '0';
	}
	if (sol->map.arr[sol->play.y - 1][sol->play.x] == '1')
		return(0);
	
	sol->play.move++;
	return (1);
}


int		ft_checkdown(t_sol *sol)
{
	if (sol->map.arr[sol->play.y + 1][sol->play.x] == 'C')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			exit(1);
		}
	}
	if (sol->map.arr[sol->play.y + 1][sol->play.x] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y + 1][sol->play.x] = '0'; 
	}
	if (sol->map.arr[sol->play.y + 1][sol->play.x] == '1')
		return(0);

	sol->play.move++;
	return (1);
}


int		ft_checkright(t_sol *sol)
{
	if (sol->map.arr[sol->play.y][sol->play.x + 1] == 'E')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			exit(1);
		}
	}
	if (sol->map.arr[sol->play.y][sol->play.x + 1] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y][sol->play.x + 1] = '0';
	}
	if (sol->map.arr[sol->play.y][sol->play.x + 1] == '1')
		return(0);
	
	sol->play.move++;
	return (1);
}

int     key_hook(int keycode, t_sol *sol)
{
//		ft_printf("Hello from key_hook! = %d\t",keycode);
		mlx_clear_window(sol->mlx, sol->win);

		if (keycode == KEY_W || keycode == KEY_UP)
		{
			if (ft_checkup(sol))
				sol->play.y--;
		}
		else if (keycode == KEY_A || keycode == KEY_LEFT)
		{
			if (ft_checkleft(sol))
				sol->play.x--;
		}
		else if (keycode == KEY_S || keycode == KEY_DOWN)
		{
			if (ft_checkdown(sol))
				sol->play.y++;
		}
		else if (keycode == KEY_D || keycode == KEY_RIGHT)
		{
			if (ft_checkright(sol))
				sol->play.x++;
		}
        else if (keycode == KEY_ESC)
        {
                mlx_destroy_window(sol->mlx, sol->win);
				ft_printf("ESC exit \n");
                exit(0);
        }
		ft_printf("player move(s) = %d\t",sol->play.move);
		ft_printf("player(x,y) = (%d, %d)\t",sol->play.x,sol->play.y);
		ft_printf("col/row (%d, %d)\t", sol->map.col, sol->map.row);
		ft_printf("coin = %d \n", sol->coin.count);
		ft_show_str(sol->box, sol, &sol->map);
		ft_playermove(sol);

        return (0);
}

void ft_playermove(t_sol *sol)
{
		int x_offset;
		int y_offset;

//	mlx_clear_window(sol->mlx, sol->win);
		x_offset = sol->play.x * sol->box / 1 + sol->box / 4;
		y_offset = sol->play.y * sol->box / 1 + sol->box / 2;
	
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0x00ff00, "{P}");
}


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
//			ft_printf("(%c) x = %d , y = %d \n",map->arr[y][x], x,y);
mlx_string_put(sol->mlx, sol->win, x_offset+5, y_offset+5, 0x666666, " 0");
			if( map->arr[y][x] == '1')
mlx_string_put(sol->mlx, sol->win, x_offset ,  y_offset , 0xffffff, "[1]");
			else if( map->arr[y][x] == 'P' && !sol->play.x && !sol->play.y)
			{
				sol->play.x = x;
				sol->play.y = y;
				map->arr[y][x] = '0';
//	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0x00ff00, "{P}");
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0x666666, " 0");
			}
			else if( map->arr[y][x] == 'E')
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0xff0066, "[E]");
			else if( map->arr[y][x] == '0') {
//	mlx_string_put(sol->mlx, sol->win, x_offset,y_offset,0x666666, " 0"); 
			}
			else if( map->arr[y][x] == 'C')
			{
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0xffff00, "(C)");
			}
			else
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0xffffff, "null");
			x++;
		}
		x = 0;
		y++;	
	}
}


void	ft_readber(int fd)
{
	int		row;
	char	*str;
	int		len;

	row = 0;
	len = 0;
	ft_printf("=============== .ber is read =================\n");
	str = get_next_line(fd);
	while (str)
	{
		row++;
		len += ft_printf("%s",str);
		str = get_next_line(fd);
	}
	ft_printf("len	= %d\n", len);
	ft_printf("each	= %d\n", len / row);
	ft_printf("row	= %d\n", row);
	ft_printf("=============== ft_readber END =================\n");
}

void	ft_collectmap(int fd, t_sol *sol)
{
	static char	*collector;

//	ft_printf("===============  ft_collectmap  START  =================\n");
	sol->coin.count = 0;
	sol->map.row = 0;
	sol->map.col = 0;
	sol->map.len = 0;
	sol->map.str = get_next_line(fd);
//	ft_printf("sol->map.str = %s\n" ,sol->map.str);
	while (sol->map.str)
	{
		sol->map.row++;
//		ft_printf("sol->map.row = %d \n" ,sol->map.row);
		sol->map.col = ft_strlen(sol->map.str);
		sol->map.len += sol->map.col;
		collector = ft_strnjoin(collector,sol->map.str);
		free(sol->map.str);
		sol->map.str = get_next_line(fd);
	}
	free(sol->map.str);
	sol->map.str = ft_strndup(collector, sol->map.len);
	free(collector);
//	ft_printf("===============  ft_collectmap  END  =================\n");
}

int	**ft_mallocmap(t_ber *map)
{
	int	**arr;
	int		times;
	
	arr = NULL;
	if (!map->str | !map->col | !map->row)
		return (NULL);
	times = 0;
	arr = malloc(sizeof(int *) * map->row + 1);
	if(!arr)
		return (NULL);
	while (times < map->row)
	{
		arr[times] = malloc(sizeof(int) * map->col);
		if (!arr[times])
			return (NULL);
		times++;
	}
//	ft_printf("mal->col = %d\n",map->col);
//	ft_printf("times = %d\n",times);
	return (arr);
}

int **ft_assignmap(int **arr, t_ber *map)
{
	int x;
	int	y;
	int	len;

	x = 0;
	y = 0;
	len = 0;
//	ft_printf("&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	while(x < map->row)
	{
		while (y < map->col)
		{
//			ft_printf("x = %d, y = %d \n", x, y);
//		if (map->str[len] == '\n')
//			map->arr[x][y] = 0;
//		else
//			ft_printf("str[len]c = %c\n",map->str[len]);
//			ft_printf("str[len]i = %d\n",map->str[len]);
//				map->arr[x][y] = ft_atoi(map->str);
			if (map->str[len] == '\n')
				map->arr[x][y] = '\0';
			else
				map->arr[x][y] = map->str[len];
//			ft_printf("(%c)",map->arr[x][y]);
//		ft_printf("arr = %c\n",arr[y][x]);
			len++;
			y++;
		}
		y = 0;
		x++;
	}
	return (arr);

}

void	ft_readmap(t_ber *map)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while(x < map->row)
	{
		while (y < map->col)
		{ 
			ft_printf("(%c)",map->arr[x][y]);
			y++;
		}
		ft_printf("\n");
		y = 0;
		x++;
	}
}

void	ft_freemap(int	**arr, t_ber *map)
{
//		ft_printf("ROW in free map = %d \n",map->row);
		int	times;

		times  = map->row ;
		while(times--)
			free(arr[times]);
		free(arr);
}

