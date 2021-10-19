/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:21:36 by htumanya          #+#    #+#             */
/*   Updated: 2021/10/18 19:21:37 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	init_globs(char **def_arg)
{
	struct timeval	tv;
	struct timezone	tz;

	g_val.death_count = 0;
	if (ft_iscap(def_arg[1]) && ft_atoi(def_arg[1]) > 0
		&& ft_iscap(def_arg[2]) && ft_atoi(def_arg[2]) > 0
		&& ft_iscap(def_arg[3]) && ft_atoi(def_arg[3]) > 0
		&& ft_iscap(def_arg[4]) && ft_atoi(def_arg[4]) > 0)
	{
		g_val.opts.num_of_philos = ft_atoi(def_arg[1]);
		g_val.opts.time_to_die = ft_atoi(def_arg[2]);
		g_val.opts.time_to_eat = ft_atoi(def_arg[3]);
		g_val.opts.time_to_sleep = ft_atoi(def_arg[4]);
	}
	if (g_val.opts.num_of_philos < 2)
		return (0);
	if (def_arg[5])
	{
		if (ft_atoi(def_arg[5]) > 0 && ft_iscap(def_arg[5]))
			g_val.opts.must_eat = ft_atoi(def_arg[5]);
	}
	else
		g_val.opts.must_eat = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			print_usage();
		if (!init_globs(argv))
		{
			printf("Wrong parameter\n");
			return (0);
		}	
		wake_philos();
		start();
	}
	else
		print_usage();
	return (0);
}
