/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floodfill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkulket <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:57:27 by tkulket           #+#    #+#             */
/*   Updated: 2023/06/22 21:57:31 by tkulket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_rev_dps(int **arr, int x, int y, int *count)
{
	if (arr[y][x] == 'C' || arr[y][x] == 'P')
		*count = *count + 1;
	if (arr[y][x] == '1')
		return ;
	else
	{
		arr[y][x] = '1';
		ft_rev_dps(arr, x, y - 1, count);
		ft_rev_dps(arr, x + 1, y, count);
		ft_rev_dps(arr, x, y + 1, count);
		ft_rev_dps(arr, x - 1, y, count);
	}
}

int	ft_rev_findpos(t_sol *sol, int value)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < sol->map.row)
	{
		while (j < sol->map.col - 1)
		{
			if (sol->map.arr[i][j] == value)
			{
				sol->map.tmp = ft_mallocmap(&sol->map);
				sol->map.tmp = ft_assignmap(sol->map.tmp, &sol->map);
				ft_rev_dps(sol->map.tmp, j, i, &count);
				ft_freemap(sol->map.tmp, &sol->map);
				if (count == sol->play.count + sol->coin.count)
					return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

/* 
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
		ft_dps(arr, x, y - 1, valid);
		ft_dps(arr, x + 1, y, valid);
		ft_dps(arr, x, y + 1, valid);
		ft_dps(arr, x - 1, y, valid);
	}
}
*/
/*
int	ft_findpos(t_sol *sol, int value, int *flag)
{
	int	i;
	int	j;
	int	found;

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
				ft_dps(sol->map.tmp, j, i, &found);
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
*/