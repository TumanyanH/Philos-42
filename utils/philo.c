#include "../philos.h"

void think(int *philo)
{
	printf_th(time_diff(g_val.times.start_time), g_val.philos[*philo].id + 1, "is thinking");
	// usleep((g_val.opts.time_to_die - g_val.opts.time_to_sleep) * 1000);
}

void ph_sleep(int *philo)
{
	printf_th(time_diff(g_val.times.start_time), g_val.philos[*philo].id + 1, "is sleeping");
	usleep(g_val.opts.time_to_eat * 1000);
}

void *start_philo(void *arg)
{
	int ph_num;

	ph_num = *((int *)arg);
	eating(*(int *)arg);
	ph_sleep((int *)arg);
	think((int *)arg);
	start_philo(arg);
	return (arg);
}

void eating(int ph)
{
	pthread_mutex_lock(&g_val.philos[ph].fork);
	printf_th(time_diff(g_val.times.start_time), ph + 1, "has taken a fork");
	if (ph + 1 != g_val.opts.num_of_philos)
		pthread_mutex_lock(&g_val.philos[ph + 1].fork);
	else 
		pthread_mutex_lock(&g_val.philos[0].fork);
	printf_th(time_diff(g_val.times.start_time), ph + 1, "has taken a fork");

	usleep(g_val.opts.time_to_eat * 1000);
	printf_th(time_diff(g_val.times.start_time), ph + 1, "is eating");

	pthread_mutex_unlock(&g_val.philos[ph].fork);
	if (ph + 1 != g_val.opts.num_of_philos)
		pthread_mutex_unlock(&g_val.philos[ph + 1].fork);
	else 
		pthread_mutex_unlock(&g_val.philos[0].fork);
	gettimeofday(&g_val.philos[ph].last_eat, NULL);
}

void init_mutex()
{
	int i = 0;

	while (i < g_val.opts.num_of_philos)
	{
		g_val.philos[i].id = i;
		g_val.philos[i].death = 0;
		pthread_mutex_init(&g_val.philos[i].fork, NULL);
		i++;
	}
	
}

void wake_philos()
{
	int i;
	int res;

	i = 0;
	g_val.philos = (t_philo *)malloc(sizeof(t_philo) * (g_val.opts.num_of_philos + 1));

	gettimeofday(&g_val.times.start_time, NULL);

	init_mutex();
	while (i < g_val.opts.num_of_philos)
	{
		res = pthread_create(&g_val.philos[i].thread, NULL, &start_philo, &g_val.philos[i].id); 
		res = pthread_create(&g_val.philos[i].ctrl_th, NULL, &ctrl, &g_val.philos[i].id);

		usleep(20);
		++i;
	}
}