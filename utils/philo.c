#include "../philos.h"

void	think(int *philo)
{
	printf_th(time_diff(g_val.times.start_time), g_val.philos[*philo].id + 1, "is thinking");
}

void	ph_sleep(int *philo)
{
	printf_th(time_diff(g_val.times.start_time), g_val.philos[*philo].id + 1, "is sleeping");
	usleep_custom(g_val.opts.time_to_eat);
}

void	*start_philo(void *arg)
{
	int ph_num;
	int counter = g_val.opts.must_eat;

	ph_num = *((int *)arg);
	while (!check_death(ph_num) && counter--)
	{
		eating(ph_num);
		ph_sleep((int *)arg);
		think((int *)arg);
	}
	return (arg);
}

void	eating(int ph)
{
	pthread_mutex_lock(&g_val.philos[ph].fork);
	printf_th(time_diff(g_val.times.start_time), ph + 1, "has taken a fork");
	if (ph + 1 != g_val.opts.num_of_philos)
		pthread_mutex_lock(&g_val.philos[ph + 1].fork);
	else 
		pthread_mutex_lock(&g_val.philos[0].fork);
	printf_th(time_diff(g_val.times.start_time), ph + 1, "has taken a fork");

	gettimeofday(&g_val.philos[ph].last_eat, NULL);
	printf_th(time_diff(g_val.times.start_time), ph + 1, "is eating");
	usleep_custom(g_val.opts.time_to_eat);

	pthread_mutex_unlock(&g_val.philos[ph].fork);
	if (ph + 1 != g_val.opts.num_of_philos)
		pthread_mutex_unlock(&g_val.philos[ph + 1].fork);
	else 
		pthread_mutex_unlock(&g_val.philos[0].fork);
}

void	init_mutex()
{
	int i;

	i = 0;
	pthread_mutex_init(&g_val.printer, NULL);
	while (i < g_val.opts.num_of_philos)
	{
		g_val.philos[i].id = i;
		g_val.philos[i].death = 0;
		pthread_mutex_init(&g_val.philos[i].fork, NULL);
		i++;
	}
	
}

void	wake_philos()
{
	int i;
	int res;

	i = 0;
	g_val.philos = (t_philo *)malloc(sizeof(t_philo) * (g_val.opts.num_of_philos + 1));

	init_mutex();
	gettimeofday(&g_val.times.start_time, NULL);
	while (i < g_val.opts.num_of_philos)
	{
		res = pthread_create(&g_val.philos[i].thread, NULL, &start_philo, &g_val.philos[i].id); 
		usleep(50);
		++i;
	}
	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		gettimeofday(&g_val.philos[i].last_eat, NULL);
		i++;
	}
	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		res = pthread_create(&g_val.philos[i].ctrl_th, NULL, &ctrl, &g_val.philos[i].id);
		++i;
	}
	
}
