#include "../philos.h"

void start()
{
	gettimeofday(&g_val.times.start_time, NULL);
	pthread_join(g_val.philos[0].thread, NULL);
}