#include "../philos.h"

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