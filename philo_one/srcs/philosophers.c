#include "philosophers.h"
static int  taken_fork_and_eat(t_global *gl, t_philo *p)
{
    pthread_mutex_lock(&gl->pickup);
    pthread_mutex_lock(&gl->forks[p->p_no]);
   	print_status(gl, p, FORK_TAKEN);
    pthread_mutex_lock((&gl->forks[p->p_no % gl->n_philo]));
    print_status(gl, p, FORK_TAKEN);
    pthread_mutex_unlock(&gl->pickup);
    pthread_mutex_lock(&gl->eats[p->p_no]);
	p->last_eat_time = get_current_time();
    pthread_mutex_unlock(&gl->eats[p->p_no]);
	print_status(gl, p, EATING);
    usleep(gl->time_to_eat * 1000);
	pthread_mutex_lock(&gl->putdown);
	pthread_mutex_unlock(&gl->forks[p->p_no]);
	pthread_mutex_unlock(&gl->forks[(p->p_no + 1) % gl->n_philo]);
	pthread_mutex_unlock(&gl->putdown);
    if ((gl->num_must_eat && ++p->num_eat == gl->num_must_eat))
		return (1);
	return (0);
}

static void *philosophing(void *vp)
{
    t_global    *gl;
    t_philo     *p;

    gl = get_global();
    p = vp;
    while(1)
    {
        print_status(gl, p, THINKING);
        if ((taken_fork_and_eat(gl, p)))
			break ;
		print_status(gl, p, SLEEPING);
    }
    pthread_mutex_lock(&gl->alive);
    gl->num_alive--;
    pthread_mutex_unlock(&gl->alive);
    return (p);
}

int         create_philo_even(t_global *gl)
{
    int i;
    int j;

    i = 0;
    while ((j = 2 * i) < gl->n_philo)
    {
        gl->philo[j].p_no = j;
        gl->philo[j].num_eat = 0;
        gl->philo[j].start_time = get_current_time();
        if (pthread_create(&gl->philo[j].thread, NULL, &philosophing, &gl->philo[j]))
            return(str_err("Error: cannot create pthread", 1));
        if (pthread_detach(gl->philo[j].thread))
            return(str_err("Error: cannot detach pthread", 1));
        if (pthread_create(&gl->philo[j].m_thread, NULL, &monitoring, &gl->philo[j]))
            return(str_err("Error: cannot create mthread", 1));
        if (pthread_detach(gl->philo[j].m_thread))
            return(str_err("Error: cannot detach mthread", 1));      
        usleep(20);
        i++;
    }
    return (0);
}

int         create_philo_odd(t_global *gl)
{
    int i;
    int j;

    i = 0;
    while ((j = (2 * i) + 1) < gl->n_philo)
    {
        gl->philo[j].p_no = j;
        gl->philo[j].num_eat = 0;
        gl->philo[j].start_time = get_current_time();
        if (pthread_create(&gl->philo[j].thread, NULL,
        &philosophing, &gl->philo[j]))
            return(str_err("Error: cannot create pthread", 1));
        if (pthread_detach(gl->philo[j].thread))
            return(str_err("Error: cannot detach pthread", 1));
        if (pthread_create(&gl->philo[j].m_thread, NULL,
        &monitoring, &gl->philo[j]))
            return(str_err("Error: cannot create mthread", 1));
        if (pthread_detach(gl->philo[j].m_thread))
            return(str_err("Error: cannot detach mthread", 1));      
        usleep(20);
        i++;
    }
    return (0);
}


int         create_philo(t_global *gl)
{
    if (!(gl->philo = malloc(sizeof(t_philo) * gl->n_philo)))
        return (str_err("Error: thread malloc failed", 1));
    if (create_philo_odd(gl))
        return (1);
    if (create_philo_even(gl))
        return (1);
    return (0);
}