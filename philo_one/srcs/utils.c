#include "philosophers.h"

unsigned    long    get_current_time()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return (1);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int                free_all(int ret)
{
    t_global	*gl;
	int			i;

	gl = get_global();
	i = 0;
	while (i < gl->n_philo)
		pthread_mutex_destroy(&gl->forks[i++]);
	pthread_mutex_destroy(&gl->alive);
	pthread_mutex_destroy(&gl->print);
	pthread_mutex_destroy(&gl->someone_died);
	pthread_mutex_destroy(&gl->putdown);
	pthread_mutex_destroy(&gl->pickup);
    if (gl->philo)
    {
        free(gl->philo);
        gl->philo = 0;
    }
    if (gl->eats)
    {
        free(gl->eats);
        gl->eats = 0;
    }
    if (gl->forks)
    {
        free(gl->forks);
        gl->forks = 0;
    }
	return (ret);
}