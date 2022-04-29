/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getTime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:51:21 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/04/28 15:51:23 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int time_us)
{
	long int	time_;

	time_ = get_time();
	while ((get_time() - time_) < (time_us / 1000))
		usleep(time_us / 10);
}

//*****************************************************************************

long	get_time(void)
{
	struct timeval	current_time;
	long int		time_exact;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		write(2, "error! gettimeofday\n", 20);
		exit(1);
	}
	time_exact = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time_exact);
}
