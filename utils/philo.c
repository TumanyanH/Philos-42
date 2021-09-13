#include "../philos.h"

void *start_philo(void *arg)
{
	printf("%d ENTERED START_PHILO AT %p\n", *((int *)arg), arg);
	eating((int *)arg);
	return (arg);
}

void eating(int *philo)
{
	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&g_val.mutex);
		printf("%d %d started eat\n", time_diff(), *philo + 1);
		usleep(g_val.opts.time_to_eat);
		pthread_mutex_unlock(&g_val.mutex);
		printf("%d %d ended eat\n", time_diff(), *philo + 1);
	}
	// if (*philo + 1 < g_val.philo_count)
	// 	(g_val.philos[*philo + 1].thread, NULL);
}

void wake_philos()
{
	int i;
	int res;

	i = 0;
	printf("i IS AT %p\n", &i);
	g_val.philos = (t_philo *)malloc(sizeof(t_philo) * (g_val.opts.num_of_philos + 1));
	printf("NUMOFPHILOS IS %d\n", g_val.opts.num_of_philos);
	while (i < g_val.opts.num_of_philos)
	{
		res = pthread_create(&g_val.philos[i].thread, NULL, &start_philo, &i);
		g_val.philos[i].fork = 0;
		if (res != 0)
			ft_exit(1);
		++i;
	}
}
