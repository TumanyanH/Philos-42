#include "../philos.h"

void start()
{
	int i = 0;
	int ret;

	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		ret = pthread_join(g_val.philos[i].thread, NULL);
		if (ret != 0)
			break;
		++i;
	}
	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		ret = pthread_join(g_val.philos[i].ctrl_th, NULL);
		if (ret != 0)
			break;
		i++;
	}
}

void *ctrl(void *arg)
{
	int ph = *((int *)arg);
	while (1)
	{
		// printf("%lu - %d\n", time_diff(g_val.philos[ph].last_eat), g_val.opts.time_to_die);
		if (time_diff(g_val.philos[ph].last_eat) > g_val.opts.time_to_die)
		{
			g_val.philos[ph].death = 1;
			printf_th(time_diff(g_val.times.start_time), ph + 1, "died");
			break;
		}
	}
	return (arg);
}

int check_death()
{
	int ret = 0;
	int i = 0;

	while (i < g_val.opts.num_of_philos)
	{
		if (g_val.philos[i].death)
			ret = 1;
		i++;
	}
	return (ret);
}