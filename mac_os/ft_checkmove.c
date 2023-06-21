


#include "libsolong.h"

int	ft_checkleft(t_sol *sol)
{
	if (sol->map.arr[sol->play.y][sol->play.x - 1] == 'E')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			ft_destroy_all(sol);
			exit (EXIT_SUCCESS);
		}
	}
	if (sol->map.arr[sol->play.y][sol->play.x - 1] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y][sol->play.x - 1] = '0';
	}
	if (sol->map.arr[sol->play.y][sol->play.x - 1] == '1')
		return (0);
	sol->play.move++;
	sol->play.x--;
	ft_printf("player move(s) = %d\n", sol->play.move);
	return (1);
}

int	ft_checkup(t_sol *sol)
{
	if (sol->map.arr[sol->play.y - 1][sol->play.x] == 'E')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			ft_destroy_all(sol);
			exit (0);
		}
	}
	if (sol->map.arr[sol->play.y - 1][sol->play.x] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y - 1][sol->play.x] = '0';
	}
	if (sol->map.arr[sol->play.y - 1][sol->play.x] == '1')
		return (0);
	sol->play.move++;
	sol->play.y--;
	ft_printf("player move(s) = %d\n", sol->play.move);
	return (1);
}

int	ft_checkdown(t_sol *sol)
{
	if (sol->map.arr[sol->play.y + 1][sol->play.x] == 'E')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			ft_destroy_all(sol);
			exit (0);
		}
	}
	if (sol->map.arr[sol->play.y + 1][sol->play.x] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y + 1][sol->play.x] = '0';
	}
	if (sol->map.arr[sol->play.y + 1][sol->play.x] == '1')
		return (0);
	sol->play.move++;
	sol->play.y++;
	ft_printf("player move(s) = %d\n", sol->play.move);
	return (1);
}

int	ft_checkright(t_sol *sol)
{
	if (sol->map.arr[sol->play.y][sol->play.x + 1] == 'E')
	{
		if (sol->coin.count == 0)
		{
			ft_printf("\n\n+*+*+*+*+*+*+*+ SUCCESS +*+*+*+*+*+*+*+\n\n");
			ft_destroy_all(sol);
			exit (0);
		}
	}
	if (sol->map.arr[sol->play.y][sol->play.x + 1] == 'C')
	{
		sol->coin.count--;
		sol->map.arr[sol->play.y][sol->play.x + 1] = '0';
	}
	if (sol->map.arr[sol->play.y][sol->play.x + 1] == '1')
		return (0);
	sol->play.move++;
	sol->play.x++;
	ft_printf("player move(s) = %d\n", sol->play.move);
	return (1);
}
