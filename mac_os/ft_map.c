

#include "libsolong.h"

void	ft_collectmap(int fd, t_sol *sol)
{
	static char	*collector;

	sol->coin.count = 0;
	sol->map.row = 0;
	sol->map.col = 0;
	sol->map.len = 0;
	sol->map.str = get_next_line(fd);
	while (sol->map.str)
	{
		sol->map.row++;
		if (sol->map.col < (int)ft_strlen(sol->map.str))
			sol->map.col = ft_strlen(sol->map.str);
		sol->map.len += sol->map.col;
		collector = ft_strnjoin(collector, sol->map.str);
		free(sol->map.str);
		sol->map.str = get_next_line(fd);
	}
	free(sol->map.str);
	sol->map.str = ft_strndup(collector, sol->map.len);
	free(collector);
}

int	**ft_mallocmap(t_ber *map)
{
	int		**arr;
	int		times;

	arr = NULL;
	if (!map->str | !map->col | !map->row)
		return (NULL);
	times = 0;
	arr = malloc(sizeof(int *) * map->row + 1);
	if (!arr)
		return (NULL);
	while (times < map->row)
	{
		arr[times] = malloc(sizeof(int) * map->col);
		if (!arr[times])
			return (NULL);
		times++;
	}
	return (arr);
}

int	**ft_assignmap(int **arr, t_ber *map)
{
	int	x;
	int	y;
	int	len;

	x = 0;
	y = 0;
	len = 0;
	while (x < map->row)
	{
		while (y < map->col)
		{
			if (map->str[len] == '\n')
				arr[x][y] = '\0';
			else
				arr[x][y] = map->str[len];
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
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->row)
	{
		while (y < map->col)
		{
			ft_printf("(%c)", arr[x][y]);
			y++;
		}
		ft_printf("\n");
		y = 0;
		x++;
	}
}

void	ft_freemap(int **arr, t_ber *map)
{
	int	times;

	times = map->row;
	while (times--)
		free(arr[times]);
	free(arr);
}
/*
void	ft_readber(int fd)
{
	int		row;
	char	*str;
	int		len;

	row = 0;
	len = 0;
	str = get_next_line(fd);
	while (str)
	{
		row++;
//		len += ft_printf("%s",str);
		len += ft_strlen(str);
		str = get_next_line(fd);
	}
//	ft_printf("len	= %d\n", len);
//	ft_printf("each	= %d\n", len / row);
//	ft_printf("row	= %d\n", row);
}

*/
