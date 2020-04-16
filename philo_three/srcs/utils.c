/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:33:33 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 11:20:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_global			*get_global(void)
{
	static t_global gl;

	return (&gl);
}

unsigned long		get_current_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int					init_global(void)
{
	t_global *gl;

	gl = get_global();
	gl->num_alive = gl->n_philo;
	clean_shm();
	if ((gl->fork = sem_open("/fork", O_CREAT, 0660, gl->n_philo))\
	== SEM_FAILED)
		return (1);
	if ((gl->eat = sem_open("/eat", O_CREAT, 0660, gl->n_philo)) == SEM_FAILED)
		return (1);
	if ((gl->pickup = sem_open("/pickup", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((gl->putdown = sem_open("/putdown", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((gl->print = sem_open("/print", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((gl->alive = sem_open("/alive", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((gl->died = sem_open("/died", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((gl->print_error = sem_open("/print_error", O_CREAT, 0660, 1))\
	== SEM_FAILED)
		return (1);
	return (0);
}

int					ft_unlink(int ret)
{
	if ((sem_unlink("/fork") == -1))
		str_error("error: sem_unlink\n", 1);
	if ((sem_unlink("/eat") == -1))
		str_error("error: sem_unlink\n", 1);
	if ((sem_unlink("/pickup") == -1))
		str_error("error: sem_unlink\n", 1);
	if ((sem_unlink("/putdown") == -1))
		str_error("error: sem_unlink\n", 1);
	if ((sem_unlink("/print") == -1))
		str_error("error: sem_unlink\n", 1);
	if ((sem_unlink("/print_error") == -1))
		str_error("error: sem_unlink\n", 1);
	if ((sem_unlink("/alive") == -1))
		str_error("error: sem_unlink\n", 1);
	if ((sem_unlink("/died") == -1))
		str_error("error: sem_unlink\n", 1);
	return (ret);
}

int					free_and_unlink(t_global *gl, int ret)
{
	sem_close(gl->fork);
	sem_close(gl->eat);
	sem_close(gl->pickup);
	sem_close(gl->putdown);
	sem_close(gl->alive);
	sem_close(gl->print);
	sem_close(gl->died);
	sem_close(gl->print_error);
	ft_unlink(0);
	free(gl->philo);
	return (ret);
}
