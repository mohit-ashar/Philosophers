/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:35:48 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 09:57:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned	long	get_current_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static		int		free_struct(void *p)
{
	if (p)
		free(p);
	p = 0;
	return (1);
}

int					free_all(int ret)
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
	free_struct((void *)gl->philo);
	free_struct((void *)gl->eats);
	free_struct((void *)gl->forks);
	return (ret);
}

int					init_mutexes(t_global *gl)
{
	if (gl == NULL)
		return (1);
	if (pthread_mutex_init(&gl->pickup, NULL))
		return (1);
	if (pthread_mutex_init(&gl->putdown, NULL))
		return (1);
	if (pthread_mutex_init(&gl->alive, NULL))
		return (1);
	if (pthread_mutex_init(&gl->print, NULL))
		return (1);
	if (pthread_mutex_init(&gl->someone_died, NULL))
		return (1);
	return (0);
}

void				ft_usleep(unsigned long time)
{
	unsigned long start;
	unsigned long time_elapsed;

	start = get_current_time();
	while (1)
	{
		time_elapsed = get_current_time() - start;
		if (time_elapsed >= time)
		{
			break ;
		}
		usleep(1);
	}
}
