/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:52:25 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/11 11:12:01 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		ft_nbr_len(unsigned long nbr)
{
	unsigned long		i;

	if (nbr == 0)
		return (1);
	i = 0;
	while (nbr > 0)
	{
		nbr = (nbr / 10);
		i++;
	}
	return (i);
}

char			*ft_itoa(unsigned long nbr)
{
	unsigned int		length;
	unsigned int		i;
	char				*result;

	i = 0;
	length = ft_nbr_len(nbr);
	if (nbr == 0)
		return (ft_strdup("0"));
	if (!(result = (char *)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	while (++i <= length)
	{
		result[length - i] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	result[length] = '\0';
	return (result);
}
