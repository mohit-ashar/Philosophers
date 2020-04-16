/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:27:20 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 16:14:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			parse_args(int ac, char **av)
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

void		*monitoring(void *vp)
{
	t_global	*gl;
	t_philo		*p;

	p = vp;
	gl = get_global();
	while (1)
	{
		if ((sem_wait(gl->eat) == -1))
			str_error("error: sem_wait\n", 1);
		if (get_current_time() - p->last_eat_time >\
		(unsigned long)gl->time_to_die)
		{
			print_status(gl, p, DIED, EXIT);
			exit(PHILO_DIED);
		}
		if ((sem_post(gl->eat) == -1))
			str_error("error: sem_wait\n", 1);
		ft_usleep(5);
	}
	return (vp);
}

void		wait_and_kill(void)
{
	t_global	*gl;
	int			i;
	int			status;

	gl = get_global();
	status = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && (WEXITSTATUS(status) == PHILO_DIED))
		{
			i = 0;
			while (i < gl->n_philo)
				kill(gl->philo[i++].pid, SIGINT);
		}
		else if (WIFEXITED(status) && (WEXITSTATUS(status) == PHILO_ATE_ENOUGH))
		{
			if (--gl->n_philo == 0)
			{
				ft_putstr_fd("Every philosopher eat enough!\n", 1);
				return ;
			}
		}
	}
}

int			main(int ac, char **av)
{
	t_global *gl;

	gl = get_global();
	if (parse_args(ac, av))
		return (str_error("error in args", 1));
	if (init_global() || create_philo1(gl))
		return (free_and_unlink(gl, 1));
	wait_and_kill();
	return (free_and_unlink(gl, 0));
}
