

#include "libsolong.h"

int	main(int argc, char **argv)
{
	int			fd;
	t_sol		*sol;

	if (argc != 2)
		return (ft_printf("input incorrect \n"));
	else
	{
		ft_printf("initializing..... \n");
		fd = open(argv[1], O_APPEND | O_RDONLY);
		if (fd < 0)
			return (ft_printf("open *.ber ERROR \n"));
		sol = malloc(sizeof(t_sol));
		ft_collectmap(fd, sol);
		close(fd);
//		ft_printf("str 	= %s\n",sol->map.str);
		ft_printf("col 	= %d\t", sol->map.col);
		ft_printf("row 	= %d\t", sol->map.row);
		ft_printf("len 	= %d\n", sol->map.len);
//		sol->play.count = ft_findartifact(sol->map.str, 'P');
//		sol->coin.count = ft_findartifact(sol->map.str, 'C');
//		sol->exit.count = ft_findartifact(sol->map.str, 'E');
//		ft_printf("play = %d\t",sol->play.count);
//		ft_printf("co(x, y) = %d, %d\n", sol->play.x, sol->play.y);
//		ft_printf("coin = %d\t",sol->coin.count);
//		ft_printf("exit = %d\n",sol->exit.count);
		if (ft_checkflag(sol))
		{
			ft_printf(" ----- > Flag PASS\n");
			sol->map.arr = ft_mallocmap(&sol->map);
			sol->map.arr = ft_assignmap(sol->map.arr, &sol->map);
			ft_startwindow(sol);
			ft_freemap(sol->map.arr, &sol->map);
		}
		else
			ft_printf(" ----- > NOOOOOOOO map\n");
		free(sol->map.str);
		free(sol);
		return (0);
	}
}
