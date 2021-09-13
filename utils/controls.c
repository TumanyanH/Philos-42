#include "../philos.h"

void start()
{
	int i = 0;
	int	*status;
	int ret;


	gettimeofday(&g_val.times.start_time, NULL);
	// pthread_join(g_val.philos[0].thread, NULL);
	
	printf("START PHILO_COUNT%d\n", g_val.opts.num_of_philos);
	while (i < g_val.opts.num_of_philos)
	{
		printf("ENTERED WHILE\n");
		ret = pthread_join(g_val.philos[i].thread, (void*)&status);
		printf("pthread_join ret=%d status=%d\n", ret, *status);
		++i;
	}
}