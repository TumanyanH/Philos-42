/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:23:01 by htumanya          #+#    #+#             */
/*   Updated: 2021/10/18 19:23:40 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	start(void)
{
	int	i;
	int	ret;

	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		ret = pthread_join(g_val.philos[i].thread, NULL);
		if (ret != 0)
			break ;
		++i;
	}
	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		ret = pthread_join(g_val.philos[i].ctrl_th, NULL);
		if (ret != 0)
			break ;
		i++;
	}
}

void	*ctrl(void *arg)
{
	int	ph;

	ph = *((int *)arg);
	while (1)
	{
		if (time_diff(g_val.philos[ph].last_eat) > g_val.opts.time_to_die)
		{
			if (g_val.opts.must_eat == -1)
				printf_th(time_diff(g_val.times.start_time), ph + 1, "died");
			g_val.philos[ph].death = 1;
			break ;
		}
	}
	return (arg);
}

int	check_death(void)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		if (g_val.philos[i].death)
			ret = 1;
		i++;
	}
	return (ret);
}
