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

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "libsolong.h"

//mlx
int		ft_findartifact(char *str,int c);
void	ft_startwindow(t_sol *sol);
int     key_hook(int keycode, t_sol *sol);
void	ft_draw_pixel(int width, int height, t_sol  *sol);
void	ft_draw_grid(int box, int width , int height, t_sol *sol);
void	ft_show_str(int box, t_sol *sol, t_ber *map);
void	ft_playermove(t_sol *sol);

// checkflag
int		ft_checkflag(t_sol *sol);
int		ft_stranger(t_sol *sol);
int		ft_noborder(t_sol *sol);

// .ber to **arr
void	ft_readber(int fd);
void	ft_collectmap(int fd, t_sol *sol);
int	**ft_mallocmap(t_ber *map);
void	ft_freemap(int	**arr, t_ber *map);
int		**ft_assignmap(int **arr, t_ber *map);
void	ft_readmap(int **arr, t_ber *map);

//	checkmove
int		ft_checkup(t_sol *sol);
int		ft_checkdown(t_sol *sol);
int		ft_checkright(t_sol *sol);
int		ft_checkleft(t_sol *sol);


//floodfill
int		ft_validpath(t_sol *sol);
int		ft_findpos(t_sol *sol, int value, int *flag);
void	ft_dps(int **arr, int x, int y, int *valid);

//create pic
//  play , coin , wall  , exit , bkgd
void	ft_init_pic(t_data *data);
void	ft_create_pic(t_sol *sol,t_data obj, char *path);

void	ft_init_pic(t_data *data)
{
	data->img = NULL;
//	data->img->ptr = NULL;
//	data->img->pixel = NULL;
//	data->img->bpp = 0;;
//	data->img->ls = 0;;
//	data->img->endian = 0;;
	data->path = NULL;
	data->move = 0;
//	data.count = 0;
	data->x = 0;
	data->y = 0;
	data->w = 64;
	data->h = 64;

}
void	ft_create_pic(t_sol *sol,t_data obj, char *path)
{
	ft_printf("path == %s \n",path);
	
	obj.img->ptr = mlx_new_image(sol->mlx, 64,64);
	obj.img->ptr = mlx_png_file_to_image(sol->mlx, path, &obj.w, &obj.h);
	obj.img->pixel  = mlx_get_data_addr(obj.img->ptr , &obj.img->bpp, &obj.img->ls, &obj.img->endian);

}

void ft_playermove(t_sol *sol)
{
		int x_offset;
		int y_offset;

//	mlx_clear_window(sol->mlx, sol->win);
		x_offset = sol->play.x * sol->box / 1 + sol->box / 4;
		y_offset = sol->play.y * sol->box / 1 + sol->box / 2;
	
	mlx_put_image_to_window(sol->mlx, sol->win, sol->play.img->ptr, x_offset, y_offset);
//	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0x00ff00, "{P}");
}

void ft_startwindow(t_sol *sol)
{

        sol->mlx = mlx_init();
		sol->box = 64;
		ft_printf("boxsize = %d  \n", sol->box);
		ft_printf("map.row = %d ,  map.col  = %d \n", sol->map.row, sol->map.col);
		ft_printf("play.w = %d ,play.h  = %d \n", sol->play.w, sol->play.h);
        sol->h = sol->box * sol->map.row;
        sol->w = sol->box * (sol->map.col - 1);
		ft_create_pic(sol,sol->play,P_PLAY);
		ft_create_pic(sol,sol->wall,P_WALL);
//		ft_init_pic(&sol->exit);
    	sol->exit.img = mlx_init();
		ft_create_pic(sol,sol->exit,P_EXIT);
//	ft_create_pic(sol,sol->sky,P_SKY);
    	sol->coin.img = mlx_init();
		ft_create_pic(sol,sol->coin,P_COIN);

		sol->win = mlx_new_window(sol->mlx, sol->w, sol->h, "Solong!");
        ft_printf(" window started ......\n");
        ft_printf("block Width = %d, Height = %d \n", sol->w, sol->h);
//		ft_readmap(&sol->map);

//		ft_draw_grid(sol->box, sol->box, sol->box, sol);
		ft_show_str(sol->box, sol, &sol->map);
		ft_printf("P( %d , %d)\n", sol->play.x, sol->play.y);
		ft_playermove(sol);

//		mlx_new_image(sol->mlx, 64, 64);
//		mlx_get_data_addr(sol->play.img->ptr, &sol->play.img->bpp, &sol->play.img->ls, &sol->play.img->endian );
//		sol->play.img = mlx_png_file_to_image(sol->mlx, P_PLAY, &sol->play.w, &sol->play.h);

        mlx_key_hook(sol->win, key_hook, sol);
        mlx_loop(sol->mlx);

}

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
			ft_printf("str 	= %s\n",sol.map.str);
			ft_printf("col 	= %d\n",sol.map.col);
			ft_printf("row 	= %d\n",sol.map.row);
			ft_printf("len 	= %d\n",sol.map.len);
		sol.play.count = ft_findartifact(sol.map.str, 'P');
		sol.coin.count = ft_findartifact(sol.map.str, 'C');
		sol.exit.count = ft_findartifact(sol.map.str, 'E');
			ft_printf("play = %d\n",sol.play.count);
			ft_printf("coin = %d\n",sol.coin.count);
			ft_printf("exit = %d\n",sol.exit.count);
		if (ft_checkflag(&sol))
		{
			ft_printf(" ----- > Flag PASS\n");
			sol.map.arr = ft_mallocmap(&sol.map);
			sol.map.arr = ft_assignmap(sol.map.arr, &sol.map);
			ft_startwindow(&sol);
			ft_freemap(sol.map.arr, &sol.map);
		}
		else
			ft_printf(" ----- > NOOOOOOOO map\n");

		free(sol.map.str);
		return (0);
	}
}

int		ft_validpath(t_sol *sol)
{
	int	player = 0;
	int coin = 0;
	int total = 0;

	total = sol->coin.count + sol->play.count;
	ft_printf("		enter valid path ..........\n");
	ft_printf("\t\t\tplay+coin = %d \n", total);
	sol->map.arr = ft_mallocmap(&sol->map);
	sol->map.arr = ft_assignmap(sol->map.arr, &sol->map);
	ft_readmap(sol->map.arr, &sol->map);

	// ff_dps of 'P' to 'E'
	ft_findpos(sol, 'P', &player);

	// ff_dps od many 'C'
	ft_findpos(sol, 'C', &coin);


	ft_printf("read main map arr......... \n");
	ft_readmap(sol->map.arr, &sol->map);
	ft_freemap(sol->map.arr, &sol->map);
	ft_printf("\t===>> Z from dps %d \n", player + coin);
	if (player + coin == sol->play.count + sol->coin.count)
		return (1);
	return (0);
}


int		ft_findpos(t_sol *sol, int value, int *flag)
{
	int i = 0;
	int j = 0;
	int a = 0;
	int b = 0;
	int z = 0;
	int found = 0;

	ft_printf("    enter  find pos.......\n");
	ft_printf(" (col, row) = %d, %d \n", sol->map.col, sol->map.row);
	a = sol->map.col - 1;
	b = sol->map.row;
	while (i < b)
	{
			while (j < a)
			{
//			ft_printf("(%c)",sol->map.arr[i][j]);
				z = sol->map.arr[i][j];
				if (z == value)
				{
					sol->map.tmp = ft_mallocmap(&sol->map);
					sol->map.tmp = ft_assignmap(sol->map.tmp, &sol->map);
					ft_readmap(sol->map.tmp, &sol->map);
					ft_printf(" '%c' (x, y) = %d, %d\n",value, j, i);
					ft_dps(sol->map.tmp, j, i , &found);
					if (found)
						*flag = *flag + 1;
						
					ft_freemap(sol->map.tmp, &sol->map);
				}
				j++;
			}
		j = 0;
		i++;
	}
	return (*flag);
}


void	ft_dps(int **arr, int x, int y, int *valid)
{
//	char c;

//	c = arr[y][x];
//	ft_printf("%d__ ", *valid);
	if (arr[y][x] == 'E')
	{
//		ft_printf("*FND*\t");
		if (*valid == 0)
			*valid = 1;
		else
			*valid = *valid + 1;
		return ;
	}
	if (arr[y][x] == '1')
	{
//		ft_printf("block\t");
		return ;
	}
	else
	{
		arr[y][x] = '1';
//		ft_printf("\t\t%c at (%d, %d)\t",c ,x ,y);
//		ft_printf("UP\n");
//		*valid = *valid + 1;
		ft_dps(arr, x , y - 1, valid);//UP
//		ft_printf("\t\t%c at (%d, %d)\t",c ,x ,y);
//		ft_printf("RG\n");
//		*valid = *valid + 10;
		ft_dps(arr, x + 1, y , valid);//RG
//		ft_printf("\t\t%c at (%d, %d)\t",c ,x ,y);
//		ft_printf("DW\n");
//		*valid = *valid + 100;
		ft_dps(arr, x , y + 1, valid);//DW
//		ft_printf("\t\t%c at (%d, %d)\t",c ,x ,y);
//		ft_printf("LF\n");
//		*valid = *valid + 1000;
		ft_dps(arr, x - 1, y , valid);//LF
	}
}




int	ft_noborder(t_sol *sol) // must check in str
{
	int col = sol->map.col;
	int row = sol->map.row;
	int	t;
	int	z;
	
	//UP
	t = 0;
	z = col - 1;
	while (t < z)
	{
		if(sol->map.str[t] != '1')
			return (1);
		t++;
	}
	//DW
	t = (row - 1) * col;
	z = ((row - 1) * col) + col - 1;
	while (t < z)
	{
		if(sol->map.str[t] != '1')
			return (1);
		t++;
	}
	//LF
	t = 0;
	while (t < row )
	{
		z = col * t;
		if (sol->map.str[z] != '1')
			return (1);
		t++;
	}
	//RG
	t = 0;
	while (t < row)
	{
		z = (col * t) + (col - 2);
		if (sol->map.str[(col * t) + (col - 2)] != '1')
			return (1);
		t++;
	}
	return (0);
}

int	ft_stranger(t_sol *sol)
{
	int x;

	x = 0;
	x += sol->play.count;
	x += sol->coin.count;
	x += sol->exit.count;
	ft_printf("stranger(X , len) = %d ,%d\n",x ,sol->map.len);
	x += ft_findartifact(sol->map.str, '0');
	x += ft_findartifact(sol->map.str, '1');
	x += ft_findartifact(sol->map.str, '\n');
	ft_printf("stranger(X , len) = %d ,%d\n",x ,sol->map.len);
	if (sol->map.len == x)
		return (0);
	return(1);
}

int	ft_checkflag(t_sol *sol)
{
	sol->play.move = 0;
	if(sol->play.count != 1)
		return (0);
	if(sol->coin.count < 1)
		return (0);
	if(sol->exit.count != 1)
		return (0);
	if(ft_noborder(sol))
		return (0);
	if(ft_validpath(sol) == 0)
		return (0);
	if(ft_stranger(sol))
		return (0);
	return (1);
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
		ft_printf("Hello from key_hook! = %d\t",keycode);
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
//mlx_put_image_to_window(sol->mlx, sol->win, sol->bkgd.img->ptr, x_offset, y_offset);
			if( map->arr[y][x] == '1')
			{
//	mlx_string_put(sol->mlx, sol->win, x_offset ,  y_offset , 0xffffff, "[1]");
	mlx_put_image_to_window(sol->mlx, sol->win, sol->wall.img->ptr, x_offset, y_offset);

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
//	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0xff0066, "[E]");
	mlx_put_image_to_window(sol->mlx, sol->win, sol->exit.img->ptr, x_offset, y_offset);

			}
			else if( map->arr[y][x] == 'C')
			{
	mlx_string_put(sol->mlx, sol->win, x_offset, y_offset, 0xffff00, "(C)");
//	mlx_put_image_to_window(sol->mlx, sol->win, sol->coin.img->ptr, x_offset, y_offset);
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
		if (sol->map.col < (int)ft_strlen(sol->map.str))
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
				arr[x][y] = '\0';
			else
				arr[x][y] = map->str[len];
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

void	ft_readmap(int **arr, t_ber *map)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while(x < map->row)
	{
		while (y < map->col)
		{ 
			ft_printf("(%c)",arr[x][y]);
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

