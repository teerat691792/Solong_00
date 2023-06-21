

#include "libsolong.h"


int		ft_validpath(t_sol *sol)
{
//	int	player = 0;
//	int coin = 0;
	int flag = 0;

	sol->map.arr = ft_mallocmap(&sol->map);
	sol->map.arr = ft_assignmap(sol->map.arr, &sol->map);
//	ft_readmap(sol->map.arr, &sol->map);
//	ft_findpos(sol, 'P', &player);
//	ft_findpos(sol, 'C', &coin);
	flag = ft_rev_findpos(sol, 'E');
	ft_freemap(sol->map.arr, &sol->map);
//	if (player + coin == sol->play.count + sol->coin.count)
	if (flag)
		return (1);
	return (0);
}

int		ft_rev_findpos(t_sol *sol, int value)
{
	int i = 0;
	int j = 0;
	int play = 0;
	int coin = 0;

	while (i < sol->map.row)
	{
			while (j < sol->map.col - 1)
			{
				if (sol->map.arr[i][j] == value) // 'E'
				{
					sol->map.tmp = ft_mallocmap(&sol->map);
					sol->map.tmp = ft_assignmap(sol->map.tmp, &sol->map);
					ft_rev_dps(sol->map.tmp, j, i , &play, &coin);
					ft_printf("p.count =  %d ,c.count = %d\tfrom sol\n", sol->play.count, sol->coin.count);
					ft_printf("play =  %d ,coin = %d\tfrom rev_dps\n", play, coin);
					ft_freemap(sol->map.tmp, &sol->map);
					if (play + coin == sol->play.count + sol->coin.count)
						return (1);
					else
						return (0);					
				}
				j++;
			}
		j = 0;
		i++;
	}
	return (0);
}


int		ft_findpos(t_sol *sol, int value, int *flag)
{
	int i = 0;
	int j = 0;
//	int found = 0;
	int play = 0;
	int coin = 0;

	while (i < sol->map.row)
	{
			while (j < sol->map.col - 1)
			{

				/*
				if (sol->map.arr[i][j] == value)
				{
					sol->map.tmp = ft_mallocmap(&sol->map);
					sol->map.tmp = ft_assignmap(sol->map.tmp, &sol->map);
					ft_dps(sol->map.tmp, j, i , &found);
					if (found)
						*flag = *flag + 1;
					ft_freemap(sol->map.tmp, &sol->map);
				}
				*/

				if (sol->map.arr[i][j] == value) // 'E'
				{
					sol->map.tmp = ft_mallocmap(&sol->map);
					sol->map.tmp = ft_assignmap(sol->map.tmp, &sol->map);
					ft_rev_dps(sol->map.tmp, j, i , &play, &coin);
					if (play + coin == sol->play.count + sol->coin.count)
					{
						ft_printf("flag++\n");
						*flag = 1;

					}
					ft_freemap(sol->map.tmp, &sol->map);
				}
				j++;
			}
		j = 0;
		i++;
	}
	ft_printf("play =  %d ,coin = %d\tfrom rev_dps\n", play, coin);
	return (*flag);
}


void	ft_rev_dps(int **arr, int x, int y, int *play, int *coin)
{
	if (arr[y][x] == 'C')
		*coin =	*coin + 1;
	if (arr[y][x] == 'P')
		*play =	*play + 1;
	if (arr[y][x] == '1')
		return ;
	else
	{
		arr[y][x] = '1';
		ft_rev_dps(arr, x , y - 1, play, coin);
		ft_rev_dps(arr, x + 1, y , play, coin);
		ft_rev_dps(arr, x , y + 1, play, coin);
		ft_rev_dps(arr, x - 1, y , play, coin);
	}
}


void	ft_dps(int **arr, int x, int y, int *valid)
{
	if (arr[y][x] == 'E')
	{
		if (*valid == 0)
			*valid = 1;
		return ;
	}
	if (arr[y][x] == '1')
		return ;
	else
	{
		arr[y][x] = '1';
		ft_dps(arr, x , y - 1, valid);
		ft_dps(arr, x + 1, y , valid);
		ft_dps(arr, x , y + 1, valid);
		ft_dps(arr, x - 1, y , valid);
	}
}


