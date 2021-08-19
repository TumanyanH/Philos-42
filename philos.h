#ifndef PHILOSOPHERS_H_
#define PHILOSOPHERS_H_

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_philo {
	pthread_t thread;
} t_philo;

typedef struct s_philo_opts {
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
} t_philo_opts;

struct s_val {
	t_philo *philos;
	int philo_count;
	t_philo_opts opts;
} g_val;

int	ft_atoi(const char *str);
void wake_philos();
void print_usage();
int check_args(int argc, char **argv);
int ft_exit();

#endif