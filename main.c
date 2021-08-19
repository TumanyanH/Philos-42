#include "philos.h"

void init_globs(char **def_arg)
{
	g_val.opts.num_of_philos = ft_atoi(def_arg[1]);
	wake_philos();
	g_val.opts.time_to_die = ft_atoi(def_arg[2]);
	g_val.opts.time_to_eat = ft_atoi(def_arg[3]);
	g_val.opts.time_to_sleep = ft_atoi(def_arg[4]);
	g_val.opts.must_eat = (def_arg[5]) ? ft_atoi(def_arg[5]) : -1;
}

int main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			print_usage();
		init_globs(argv);
		
	}
	else 
		print_usage();

	ft_exit();
	return (0);
}