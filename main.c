#include "philos.h"

void	init_globs(char **def_arg)
{
	struct timeval	tv;
	struct timezone	tz;

	if (ft_atoi(def_arg[1]) > 0 &&
		ft_atoi(def_arg[2]) > 0 && ft_atoi(def_arg[3]) > 0 \
			&& ft_atoi(def_arg[4]) > 0)
	{
		g_val.opts.num_of_philos = ft_atoi(def_arg[1]);
		g_val.opts.time_to_die = ft_atoi(def_arg[2]);
		g_val.opts.time_to_eat = ft_atoi(def_arg[3]);
		g_val.opts.time_to_sleep = ft_atoi(def_arg[4]);
	}
	if (def_arg[5])
	{
		if (ft_atoi(def_arg[5]) > 0)
			g_val.opts.must_eat = ft_atoi(def_arg[5]);
	}
	else
		g_val.opts.must_eat = -1;
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			print_usage();
		init_globs(argv);
		wake_philos();
		start();
	}
	else
		print_usage();
	return (0);
}
