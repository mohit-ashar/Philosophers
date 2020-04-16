/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:06:57 by user42            #+#    #+#             */
/*   Updated: 2020/04/13 13:07:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		str_error(char *err_msg, int ret)
{
	t_global *gl;

	gl = get_global();
	sem_wait(gl->print_error);
	ft_putstr_fd(err_msg, 2);
	sem_post(gl->print_error);
	return (ret);
}
