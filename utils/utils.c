/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:22:37 by htumanya          #+#    #+#             */
/*   Updated: 2021/10/18 19:22:38 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

void	print_usage(void)
{
	printf("\nusage : ./philo\n");
	printf("\n\t 1. number_of_philosophers");
	printf("\n\t 2. time_to_die");
	printf("\n\t 3. time_to_eat");
	printf("\n\t 4. time_to_sleep");
	printf("\n\t 5. [number_of_times_each_philosopher_must_eat]\n");
	exit(0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		++i;
	}
	return (1);
}

long int	time_diff(struct timeval start_time)
{
	struct timeval		cur_time;
	long int			start;

	start = ((long int)start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	gettimeofday(&cur_time, NULL);
	return ((((long int)cur_time.tv_sec * 1000)
			+ ((int)cur_time.tv_usec / 1000)) - start);
}
