#include "../philos.h"

void start()
{
	int i = 0;
	int ret;

	i = 0;
	while (i < g_val.opts.num_of_philos)
	{
		ret = pthread_join(g_val.philos[i].thread, NULL);
		++i;
	}
}