#include "../philos.h"

void think(int *philo)
{
	printf("%d %d started thinking\n", time_diff(), g_val.philos[*philo].id);
	usleep(g_val.opts.time_to_die - g_val.opts.time_to_eat);
	printf("%d %d ended thinking\n", time_diff(), g_val.philos[*philo].id);
}

void ph_sleep(int *philo)
{
	printf("%d %d started sleeping\n", time_diff(), g_val.philos[*philo].id);
	usleep(g_val.opts.time_to_eat);
	printf("%d %d ended sleeping\n", time_diff(), g_val.philos[*philo].id);
}

void *start_philo(void *arg)
{
	eating((int *)arg);
	think((int *)arg);
	pthread_join(g_val.philos[*((int *)arg)].thread, NULL);
	return (arg);
}

void eating(int *philo)
{
	pthread_mutex_lock(&g_val.philos[*philo].fork);
	printf("%d %d started eat\n", time_diff(), g_val.philos[*philo].id);
	usleep(g_val.opts.time_to_eat);
	printf("%d %d ended eat\n", time_diff(), g_val.philos[*philo].id);
	pthread_mutex_unlock(&g_val.philos[*philo].fork);
}

void wake_philos()
{
	int i;
	int res;

	i = 0;
	g_val.philos = (t_philo *)malloc(sizeof(t_philo) * (g_val.opts.num_of_philos + 1));
	while (i < g_val.opts.num_of_philos)
	{
		g_val.philos[i].id = i + 1;	
		res = pthread_create(&g_val.philos[i].thread, NULL, &start_philo, &i);
		pthread_mutex_init(&g_val.philos[i].fork, NULL);
		if (res != 0)
			ft_exit(1);
		++i;
	}
}
