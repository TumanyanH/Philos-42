#include "../philos.h"

void *start_philo(void *arg)
{
	return (0);
}

void wake_philos()
{
	int i = 0;

	g_val.philos = (t_philo *)malloc(sizeof(t_philo) * (g_val.opts.num_of_philos + 1));
	while (i < g_val.opts.num_of_philos)
	{
		pthread_create(&g_val.philos[i].thread, NULL, start_philo, NULL);
		++i;
	}
}