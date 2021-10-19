/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:22:43 by htumanya          #+#    #+#             */
/*   Updated: 2021/10/18 19:22:44 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	printf_th(long int time, int ph_count, char *string)
{
	if (!check_death())
	{
		if (g_val.death_count < 2)
		{
			pthread_mutex_lock(&g_val.printer);
			printf("%lu %d %s\n", time, ph_count, string);
			pthread_mutex_unlock(&g_val.printer);
		}
	}
}

void	usleep_custom(int time)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	while (time_diff(cur_time) < time)
		usleep(50);
}

void	create_threads(void)
{
	int	i;
	int	res;

	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		res = pthread_create(&g_val.philos[i].thread, NULL,
				&start_philo, &g_val.philos[i].id);
		usleep(50);
		++i;
	}
}

void	wake_philos(void)
{
	int	i;
	int	res;

	i = sizeof(t_philo) * (g_val.opts.num_of_philos + 1);
	g_val.philos = (t_philo *)malloc(i);
	i = 0;
	init_mutex();
	gettimeofday(&g_val.times.start_time, NULL);
	create_threads();
	while (i < g_val.opts.num_of_philos)
	{
		gettimeofday(&g_val.philos[i].last_eat, NULL);
		i++;
	}
	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		res = pthread_create(&g_val.philos[i].ctrl_th, NULL,
				&ctrl, &g_val.philos[i].id);
		++i;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
