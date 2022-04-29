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

//*****************************************************************************

void	print_messag(t_info *info, int key)
{
	long int	time;

	time = get_time() - info->t0;
	pthread_mutex_lock(&info->print_mutex);
	if (key == TAKE_LEFT)
		printf("%ld | %d has take left fork\n", time, info->node->index);
	else if (key == TAKE_RIGHT)
		printf("%ld | %d has take right fork\n", time, info->node->index);
	else if (key == PUT_LEFT)
		printf("%ld | %d has put left fork\n", time, info->node->index);
	else if (key == PUT_RIGHT)
		printf("%ld | %d has put right fork\n", time, info->node->index);
	else if (key == DEAD)
		printf("%ld | %d dead\n", time, info->node->index);
	else if (key == SLEEP)
		printf("%ld | %d is sleeping\n", time, info->node->index);
	else if (key == THINK)
		printf("%ld | %d is think\n", time, info->node->index);
	else if (key == EAT)
		printf("%ld | %d is eating\n", time, info->node->index);
	pthread_mutex_unlock(&info->print_mutex);
}
