

#include "libsolong.h"


int	ft_noborder_up_dw(t_sol *sol)
{
	int	col;
	int	row;
	int	t;
	int	z;

	col = sol->map.col;
	row = sol->map.row;
	t = 0;
	z = col - 1;
	while (t < z)
	{
		if (sol->map.str[t] != '1')
			return (1);
		t++;
	}
	t = (row - 1) * col;
	z = ((row - 1) * col) + col - 1;
	while (t < z)
	{
		if (sol->map.str[t] != '1')
			return (1);
		t++;
	}
	return (0);
}

int	ft_noborder_lf_rg(t_sol *sol)
{
	int	col;
	int	row;
	int	t;
	int	z;

	t = 0;
	col = sol->map.col;
	row = sol->map.row;
	while (t < row)
	{
		z = col * t;
		if (sol->map.str[z] != '1')
			return (1);
		t++;
	}
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
	int	x;

	x = 0;
	x += sol->play.count;
	x += sol->coin.count;
	x += sol->exit.count;
	x += ft_findartifact(sol->map.str, '0');
	x += ft_findartifact(sol->map.str, '1');
	ft_printf("x = %d\n");
	if (x == (sol->map.col - 1) * sol->map.row)
		return (0);
	return (1);
}

int	ft_checkflag(t_sol *sol)
{
	sol->play.move = 0;
	sol->play.count = ft_findartifact(sol->map.str, 'P');
	if (sol->play.count != 1)
		return (0);
	sol->coin.count = ft_findartifact(sol->map.str, 'C');
	if (sol->coin.count < 1)
		return (0);
	sol->exit.count = ft_findartifact(sol->map.str, 'E');
	if (sol->exit.count != 1)
		return (0);
	if (ft_noborder_up_dw(sol))
		return (0);
	if (ft_noborder_lf_rg(sol))
		return (0);
	if (ft_stranger(sol))
		return (0);
	if (ft_validpath(sol) == 0)
		return (0);
	return (1);
}

int	ft_findartifact(char *str, int c)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
