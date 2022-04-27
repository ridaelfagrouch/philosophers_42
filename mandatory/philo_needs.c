/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_needs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:54:55 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/04/20 14:54:58 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int time)
{
	long int	time_;

	time_ = get_time();
	while ((get_time() - time_) < time)
		usleep(time);
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

void	take_forks(t_info *info)
{
	pthread_mutex_lock(&info->node->mutex);
	pthread_mutex_lock(&info->tmp->mutex);
	printf("%ld philosopher %d has take left fork\n", \
		(get_time() - info->t0), info->node->index);
	printf("%ld philosopher %d has take right fork\n", \
		(get_time() - info->t0), info->node->index);
	info->node->fork_statu = on;
	info->tmp->fork_statu = on;
}

//*****************************************************************************

void	put_forks(t_info *info)
{
	printf("%ld philosopher %d has put left fork\n", \
		(get_time() - info->t0), info->node->index);
	info->node->fork_statu = off;
	printf("%ld philosopher %d has put right fork\n", \
		(get_time() - info->t0), info->node->index);
	info->tmp->fork_statu = off;
}

//*****************************************************************************

void	start_routine(t_info *info)
{
	if (info->node == info->heade)
		info->tmp = info->tail;
	else
		info->tmp = info->node->prev;
	if (info->tmp->fork_statu == off && info->node->fork_statu == off)
	{
		if (info->dead_statu == true)
		{
			printf("%ld philosopher %d dead\n", \
				(get_time() - info->t0), info->node->index);
			exit(1);
		}
		take_forks(info);
		if ((get_time() - info->node->last_meal) > info->time_to_die && \
			(info->node->nmb_of_eat != 0))
			info->dead_statu = true;
		printf("%ld philosopher %d is eating\n", \
			(get_time() - info->t0), info->node->index);
		ft_usleep(info->time_to_eat);
		info->node->last_meal = get_time();
		info->node->nmb_of_eat++;
		if (info->node->nmb_of_eat == info->nmb_of_time_eat)
			info->cont_eat++;
		if (info->cont_eat == info->nmb_of_thread)
		{
			printf("%ld all philosophers eat\n", (get_time() - info->t0));
			exit(1);
		}
		put_forks(info);
		printf("%ld philosopher %d is sleeping\n", \
			(get_time() - info->t0), info->node->index);
		ft_usleep(info->time_to_sleep);
		printf("%ld philosopher %d is think\n", \
			(get_time() - info->t0), info->node->index);
		pthread_mutex_unlock(&info->node->mutex);
		pthread_mutex_unlock(&info->tmp->mutex);
	}
}
