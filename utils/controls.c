#include "../philos.h"

void start()
{
	int i = 0;
	int ret;


	gettimeofday(&g_val.times.start_time, NULL);
	while (i < g_val.opts.num_of_philos)
	{
		ret = pthread_join(g_val.philos[i].thread, NULL);
		++i;
	}
}