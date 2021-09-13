#include "../philos.h"

void *start_philo(void *arg)
{
	eating();
	return (arg);
}

void eating()
{
	pthread_mutex_lock(&g_val.mutex);
	printf("%d 1 started eat\n", time_diff());
	usleep(g_val.opts.time_to_eat);
	printf("%d 1 ended eat\n", time_diff());
	pthread_mutex_unlock(&g_val.mutex);
}

void wake_philos()
{
	int i;
	int res;

	i = 0;
	g_val.philos = (t_philo *)malloc(sizeof(t_philo) * (g_val.opts.num_of_philos + 1));
	while (i < g_val.opts.num_of_philos)
	{
		res = pthread_create(&g_val.philos[i].thread, NULL, &start_philo, NULL);
		g_val.philos[i].fork = 0;
		if (res != 0)
			ft_exit(1);
		++i;
	}
}
