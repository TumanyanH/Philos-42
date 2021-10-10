#include "../philos.h"

int	ft_atoi(const char *str)
{
	int neg;
	int i;
	int num;

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

void	print_usage()
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
	int i = 0;
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
	struct timeval cur_time;
	long int start = ((long int)start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);

	gettimeofday(&cur_time, NULL);
	return ((((long int)cur_time.tv_sec * 1000) + ((int)cur_time.tv_usec / 1000))
			- start);
}


int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	printf_th(long int time, int ph_count, char *string)
{
	if (!check_death())
	{
		pthread_mutex_lock(&g_val.printer);
		printf("%lu %d %s\n", time, ph_count, string);
		pthread_mutex_unlock(&g_val.printer);
	}
	
}

void	usleep_custom(int time)
{
	struct timeval cur_time;

	gettimeofday(&cur_time, NULL);
	while (time_diff(cur_time) < time)
		usleep(20);
}