/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:13:56 by htumanya          #+#    #+#             */
/*   Updated: 2021/10/18 19:13:57 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_t		ctrl_th;
	pthread_mutex_t	fork;
	struct timeval	last_eat;
	int				death;
}					t_philo;

typedef struct s_philo_opts
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
}					t_philo_opts;

typedef struct s_times
{
	struct timeval	start_time;
}					t_times;

struct				s_val
{
	t_philo			*philos;
	pthread_mutex_t	printer;
	pthread_mutex_t	def;
	pthread_mutex_t	eating;
	t_philo_opts	opts;
	t_times			times;
	int				death_count;
}					g_val;

int			ft_atoi(const char *str);
void		wake_philos(void);
void		print_usage(void);
int			check_args(int argc, char **argv);
long int	time_diff(struct timeval start_time);
void		start(void);
void		eating(int philo);
void		printf_th(long int time, int ph_count, char *string);
void		*ctrl(void *arg);
int			check_death(void);
void		usleep_custom(int time);
void		*start_philo(void *arg);
void		init_mutex(void);
int			ft_iscap(char *string);
int			ft_strcmp(char *s1, char *s2);

#endif
