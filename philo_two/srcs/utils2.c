/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:42:29 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 10:16:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void				clean_shm(void)
{
	sem_unlink("/fork");
	sem_unlink("/eat");
	sem_unlink("/pickup");
	sem_unlink("/putdown");
	sem_unlink("/print");
	sem_unlink("/alive");
	sem_unlink("/died");
	sem_unlink("/print_error");
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
