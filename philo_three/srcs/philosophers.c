/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:30:16 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 10:46:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			take_fork_and_eat(t_global *gl, t_philo *p)
{
	if ((sem_wait(gl->pickup) == -1))
		str_error("error: sem_wait\n", 1);
	if ((sem_wait(gl->fork) == -1))
		str_error("error: sem_wait\n", 1);
	print_status(gl, p, TAKEN_FORK, NO_EXIT);
	if ((sem_wait(gl->fork) == -1))
		str_error("error: sem_wait\n", 1);
	print_status(gl, p, TAKEN_FORK, NO_EXIT);
	print_status(gl, p, EATING, NO_EXIT);
	if ((sem_post(gl->pickup) == -1))
		str_error("error: sem_post\n", 1);
	if ((sem_wait(gl->eat) == -1))
		str_error("error: sem_wait\n", 1);
	p->last_eat_time = get_current_time();
	if ((sem_post(gl->eat) == -1))
		str_error("error: sem_post\n", 1);
	ft_usleep(gl->time_to_eat);
	if ((sem_wait(gl->putdown) == -1))
		str_error("error: sem_wait\n", 1);
	if ((sem_post(gl->fork) == -1) || (sem_post(gl->fork) == -1))
		str_error("error: sem_wait\n", 1);
	if ((sem_post(gl->putdown) == -1))
		str_error("error: sem_post\n", 1);
	return (gl->num_must_eat == ++p->no_eaten ? 1 : 0);
}

void		philosophing(void *vp)
{
	t_global	*gl;
	t_philo		*p;

	p = vp;
	gl = get_global();
	if (pthread_create(&p->thread, NULL, &monitoring, p))
		exit(str_error("Error: failed to create thread 'monitor'\n", 1));
	if (pthread_detach(p->thread))
		exit(str_error("Error: failed to detach thread 'monitor'\n", 1));
	while (1)
	{
		print_status(gl, p, THINKING, NO_EXIT);
		if (take_fork_and_eat(gl, p))
			exit(PHILO_ATE_ENOUGH);
		print_status(gl, p, SLEEPING, NO_EXIT);
		ft_usleep(gl->time_to_sleep);
	}
	exit(0);
}

int			create_philo1(t_global *gl)
{
	int				i;
	t_philo			*philo;
	unsigned long	time;

	i = 0;
	if (!(philo = malloc(sizeof(t_philo) * gl->n_philo)))
		return (1);
	time = get_current_time();
	gl->philo = philo;
	while (i < gl->n_philo)
	{
		gl->philo[i].p_no = i;
		gl->philo[i].no_eaten = 0;
		gl->philo[i].start_time = time;
		gl->philo[i].last_eat_time = gl->philo[i].start_time;
		if ((gl->philo[i].pid = fork()) == 0)
			philosophing(&gl->philo[i]);
		i++;
	}
	return (0);
}
