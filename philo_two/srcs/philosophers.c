/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:13:59 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 15:25:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				take_fork_and_eat(t_global *gl, t_philo *p)
{
	if ((sem_wait(gl->pickup) == -1))
		str_error("error: sem_wait\n", 1);
	if ((sem_wait(gl->fork) == -1))
		str_error("error: sem_wait\n", 1);
	print_status(gl, p, TAKEN_FORK);
	if ((sem_wait(gl->fork) == -1))
		str_error("error: sem_wait\n", 1);
	print_status(gl, p, TAKEN_FORK);
	if ((sem_post(gl->pickup) == -1))
		str_error("error: sem_post\n", 1);
	if ((sem_wait(gl->eat) == -1))
		str_error("error: sem_wait\n", 1);
	p->last_eat_time = get_current_time();
	if ((sem_post(gl->eat) == -1))
		str_error("error: sem_post\n", 1);
	print_status(gl, p, EATING);
	ft_usleep(gl->time_to_eat);
	if ((sem_wait(gl->putdown) == -1))
		str_error("error: sem_wait\n", 1);
	if ((sem_post(gl->fork) == -1) || (sem_post(gl->fork) == -1))
		str_error("error: sem_wait\n", 1);
	if ((sem_post(gl->putdown) == -1))
		str_error("error: sem_post\n", 1);
	return (gl->num_must_eat == ++p->no_eaten ? 1 : 0);
}

void			*philosophing(void *vp)
{
	t_global	*gl;
	t_philo		*p;

	p = vp;
	gl = get_global();
	while (1)
	{
		print_status(gl, p, THINKING);
		if (take_fork_and_eat(gl, p))
			break ;
		print_status(gl, p, SLEEPING);
		ft_usleep(gl->time_to_sleep);
	}
	if ((sem_wait(gl->alive) == -1))
		str_error("error: sem_wait\n", 1);
	gl->num_alive--;
	if ((sem_post(gl->alive) == -1))
		str_error("error: sem_post\n", 1);
	return (p);
}

int				create_even_philo(t_global *gl, unsigned long start_time)
{
	int i;
	int j;

	i = 0;
	while ((j = (2 * i) + 1) < gl->n_philo)
	{
		gl->philo[j].p_no = j;
		gl->philo[j].no_eaten = 0;
		gl->philo[j].start_time = start_time;
		gl->philo[j].last_eat_time = gl->philo[j].start_time;
		if ((pthread_create(&gl->philo[j].thread, NULL, &philosophing,
		&gl->philo[j])))
			return (1);
		if ((pthread_detach(gl->philo[j].thread)))
			return (1);
		if ((pthread_create(&gl->philo[j].m_thread, NULL, &monitoring,
		&gl->philo[j])))
			return (1);
		if ((pthread_detach(gl->philo[j].m_thread)))
			return (1);
		i++;
	}
	return (0);
}

int				create_odd_philo(t_global *gl, unsigned long start_time)
{
	int i;
	int j;

	i = 0;
	while ((j = 2 * i) < gl->n_philo)
	{
		gl->philo[j].p_no = j;
		gl->philo[j].no_eaten = 0;
		gl->philo[j].start_time = start_time;
		gl->philo[j].last_eat_time = gl->philo[j].start_time;
		if ((pthread_create(&gl->philo[j].thread, NULL, &philosophing,
		&gl->philo[j])))
			return (1);
		if ((pthread_detach(gl->philo[j].thread)))
			return (1);
		if ((pthread_create(&gl->philo[j].m_thread, NULL, &monitoring,
		&gl->philo[j])))
			return (1);
		if ((pthread_detach(gl->philo[j].m_thread)))
			return (1);
		i++;
	}
	return (0);
}

int				create_philo(t_global *gl)
{
	t_philo			*philo;
	unsigned long	start_time;

	if (!(philo = malloc(sizeof(t_philo) * gl->n_philo)))
		return (1);
	start_time = get_current_time();
	gl->philo = philo;
	if (create_odd_philo(gl, start_time) || create_even_philo(gl, start_time))
		return (1);
	return (0);
}
