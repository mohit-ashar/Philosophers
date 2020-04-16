/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:08:15 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 10:17:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					parse_args(int ac, char **av)
{
	t_global *gl;

	gl = get_global();
	if (ac < 5 || ac > 6)
		return (1);
	if ((gl->n_philo = ft_atoi(av[1])) <= 1)
		return (1);
	if ((gl->time_to_die = ft_atoi(av[2])) <= 0)
		return (1);
	if ((gl->time_to_eat = ft_atoi(av[3])) <= 0)
		return (1);
	if ((gl->time_to_sleep = ft_atoi(av[4])) <= 0)
		return (1);
	if (ac == 6)
	{
		if ((gl->num_must_eat = (ft_atoi(av[5]))) <= 0)
			return (1);
		else
			gl->num_must_eat = -1;
	}
	return (0);
}

void				*monitoring(void *vp)
{
	t_global	*gl;
	t_philo		*p;

	p = vp;
	gl = get_global();
	while (1)
	{
		if ((sem_wait(gl->eat) == -1))
			str_error("error: sem_wait\n", 1);
		if (get_current_time() - p->last_eat_time > (unsigned)gl->time_to_die)
		{
			print_status(gl, p, DIED);
			if ((sem_wait(gl->died) == -1))
				str_error("error: sem_wait\n", 1);
			gl->died_flag = 1;
			if ((sem_post(gl->died) == -1))
				str_error("error: sem_post\n", 1);
			break ;
		}
		if ((sem_post(gl->eat) == -1))
			str_error("error: sem_wait\n", 1);
		ft_usleep(100);
	}
	return (p);
}

int					main(int ac, char **av)
{
	t_global *gl;

	if ((gl = get_global()) && parse_args(ac, av))
		return (str_error("error in args", 1));
	if (init_global() || create_philo(gl))
		return (free_and_unlink(gl, 0));
	while (1)
	{
		if ((sem_wait(gl->alive) == -1))
			return (str_error("error: sem_wait\n", 1));
		if (gl->num_alive == 0)
			break ;
		if ((sem_post(gl->alive) == -1))
			return (str_error("error: sem_post\n", 1));
		if ((sem_wait(gl->died) == -1))
			return (str_error("error: sem_wait\n", 1));
		if (gl->died_flag == 1)
			return (ft_unlink(1));
		if ((sem_post(gl->died) == -1))
			return (str_error("error: sem_post\n", 1));
		ft_usleep(100);
	}
	if (!(gl->died_flag))
		str_error("philosophers eat enough!\n", 0);
	return (free_and_unlink(gl, 0));
}
