/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:13:45 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 15:53:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_global		*get_global(void)
{
	static t_global gl;

	return (&gl);
}

int				parse(int ac, char **av)
{
	t_global *gl;

	gl = get_global();
	if (ac < 5 || ac > 6)
		return (1);
	if ((gl->n_philo = ft_atoi(av[1])) <= 1)
		return (1);
	if ((gl->time_to_die = ft_atoi(av[2])) < 0)
		return (1);
	if ((gl->time_to_eat = ft_atoi(av[3])) < 0)
		return (1);
	if ((gl->time_to_sleep = ft_atoi(av[4])) < 0)
		return (1);
	if (ac == 6)
	{
		if ((gl->num_must_eat = ft_atoi(av[5])) < 0)
			return (1);
	}
	else
		gl->num_must_eat = -1;
	return (0);
}

int				init_global(t_global *gl)
{
	int i;

	i = 0;
	gl->num_alive = gl->n_philo;
	if (!(gl->forks = malloc(sizeof(pthread_mutex_t) * gl->n_philo)))
		return (1);
	if (!(gl->eats = malloc(sizeof(pthread_mutex_t) * gl->n_philo)))
		return (1);
	while (i < gl->n_philo)
	{
		if (pthread_mutex_init(&gl->forks[i], NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < gl->n_philo)
	{
		if (pthread_mutex_init(&gl->eats[i], NULL))
			return (1);
		i++;
	}
	if (init_mutexes(gl))
		return (1);
	return (0);
}

void			*monitoring(void *vp)
{
	t_global	*gl;
	t_philo		*p;

	p = vp;
	gl = get_global();
	while (1)
	{
		pthread_mutex_lock(&gl->eats[p->p_no]);
		if (get_current_time() - p->last_eat_time\
		> (unsigned long)gl->time_to_die)
		{
			print_status(gl, p, DIED);
			pthread_mutex_lock(&gl->someone_died);
			gl->flag_died = 1;
			pthread_mutex_unlock(&gl->someone_died);
		}
		pthread_mutex_unlock(&gl->eats[p->p_no]);
		ft_usleep(5);
	}
}

int				main(int ac, char **av)
{
	t_global *gl;

	gl = get_global();
	if (parse(ac, av))
		exit(1);
	if (init_global(gl) || create_philo(gl))
		return (free_all(1));
	while (1)
	{
		pthread_mutex_lock(&gl->alive);
		if (gl->num_alive == 0)
			break ;
		pthread_mutex_unlock(&gl->alive);
		pthread_mutex_lock(&gl->someone_died);
		if (gl->flag_died)
			return (EXIT_SUCCESS);
		pthread_mutex_unlock(&gl->someone_died);
		ft_usleep(5);
	}
	if (!gl->flag_died)
		ft_putstr_fd("Every philosopher eat enough!\n", 1);
	return (free_all(0));
}
