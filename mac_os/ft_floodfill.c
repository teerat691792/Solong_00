

#include "libsolong.h"


int	ft_validpath(t_sol *sol)
{
	int	flag;

	flag = 0;
	sol->map.arr = ft_mallocmap(&sol->map);
	sol->map.arr = ft_assignmap(sol->map.arr, &sol->map);
	flag = ft_rev_findpos(sol, 'E');
	ft_freemap(sol->map.arr, &sol->map);
	if (flag)
		return (1);
	return (0);
}

int	ft_rev_findpos(t_sol *sol, int value)
{
	int i;
	int j;
	int play;
	int coin;

	i = 0;
	j = 0;
	play = 0;
	coin = 0;
	while (i < sol->map.row)
	{
		while (j < sol->map.col - 1)
		{
			if (sol->map.arr[i][j] == value)
			{
				sol->map.tmp = ft_mallocmap(&sol->map);
				sol->map.tmp = ft_assignmap(sol->map.tmp, &sol->map);
				ft_rev_dps(sol->map.tmp, j, i , &play, &coin);
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

int	ft_findpos(t_sol *sol, int value, int *flag)
{
	int i;
	int j;
	int found;

	i = 0;
	j = 0;
	found = 0;
	while (i < sol->map.row)
	{
		while (j < sol->map.col - 1)
		{
			if (sol->map.arr[i][j] == value)
			{
				sol->map.tmp = ft_mallocmap(&sol->map);
				sol->map.tmp = ft_assignmap(sol->map.tmp, &sol->map);
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
