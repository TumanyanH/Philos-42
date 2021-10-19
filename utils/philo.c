/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:06 by htumanya          #+#    #+#             */
/*   Updated: 2021/10/18 19:25:08 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	think(int *philo)
{
	printf_th(time_diff(g_val.times.start_time),
		g_val.philos[*philo].id + 1, "is thinking");
}

void	ph_sleep(int *philo)
{
	printf_th(time_diff(g_val.times.start_time),
		g_val.philos[*philo].id + 1, "is sleeping");
	usleep_custom(g_val.opts.time_to_eat);
}

void	*start_philo(void *arg)
{
	int	ph_num;
	int	counter;

	ph_num = *((int *)arg);
	counter = g_val.opts.must_eat;
	while (!check_death() && counter--)
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

void	init_mutex(void)
{
	int	i;

	i = 0;
	pthread_mutex_init(&g_val.printer, NULL);
	pthread_mutex_init(&g_val.def, NULL);
	while (i < g_val.opts.num_of_philos)
	{
		g_val.philos[i].id = i;
		g_val.philos[i].death = 0;
		pthread_mutex_init(&g_val.philos[i].fork, NULL);
		i++;
	}
}
