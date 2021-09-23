#include "../philos.h"

void think(int *philo)
{
	printf_th(time_diff(), g_val.philos[*philo].id + 1, "is thinking");
	usleep((g_val.opts.time_to_die - g_val.opts.time_to_sleep) * 1000);
	// printf_th(time_diff(), g_val.philos[*philo].id, "started thinking");
}

void ph_sleep(int *philo)
{
	printf_th(time_diff(), g_val.philos[*philo].id + 1, "is sleeping");
	usleep(g_val.opts.time_to_eat * 1000);
	// printf_th(time_diff(), g_val.philos[*philo].id, "ended sleeping");
}

void *start_philo(void *arg)
{
	eating((int *)arg);
	ph_sleep((int *)arg);
	think((int *)arg);
	start_philo(arg);
	return (arg);
}

void eating(int *philo)
{
	pthread_mutex_lock(&g_val.philos[*philo].fork);
	printf_th(time_diff(), g_val.philos[*philo].id + 1, "has taken a fork");
	if (*philo + 1 == g_val.opts.num_of_philos)
		pthread_mutex_lock(&g_val.philos[*philo + 1].fork);
	else 
		pthread_mutex_lock(&g_val.philos[0].fork);
	printf_th(time_diff(), g_val.philos[*philo].id + 1, "has taken a fork");
	printf_th(time_diff(), g_val.philos[*philo].id + 1, "is eating");
	usleep(g_val.opts.time_to_eat * 1000);
	// printf_th(time_diff(), g_val.philos[*philo].id, "ended eat");
	pthread_mutex_unlock(&g_val.philos[*philo].fork);
	if (*philo + 1 == g_val.opts.num_of_philos)
		pthread_mutex_unlock(&g_val.philos[*philo + 1].fork);
	else 
		pthread_mutex_unlock(&g_val.philos[0].fork);
}

void wake_philos()
{
	int i;
	int res;

	i = 0;
	g_val.philos = (t_philo *)malloc(sizeof(t_philo) * (g_val.opts.num_of_philos + 1));
	while (i < g_val.opts.num_of_philos)
	{
		g_val.philos[i].id = i;	
		res = pthread_create(&g_val.philos[i].thread, NULL, &start_philo, &g_val.philos[i].id); 
		pthread_mutex_init(&g_val.philos[i].fork, NULL);
		if (res != 0)
			ft_exit(1);
		++i;
	}
}