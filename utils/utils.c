#include "../philos.h"

int	ft_atoi(const char *str)
{
	int neg;
	int i;
	int num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

void print_usage()
{
	printf("\nusage : ./philo\n");
	printf("\n\t 1. number_of_philosophers");
	printf("\n\t 2. time_to_die");
	printf("\n\t 3. time_to_eat");
	printf("\n\t 4. time_to_sleep");
	printf("\n\t 5. [number_of_times_each_philosopher_must_eat]\n");
	exit(0);
}

int ft_exit(int kill_threads)
{
	int i;

	i = 0;
	if (kill_threads)
	{
		while (i < g_val.opts.num_of_philos)
		{
			pthread_detach(g_val.philos[i].thread);
			++i;
		}
	}
	exit(0);
}

int check_args(int argc, char **argv)
{
	int i = 0;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		++i;
	}
	return (1);
}

int time_diff()
{
	struct timeval cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_usec - g_val.times.start_time.tv_usec);
}