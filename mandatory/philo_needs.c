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

void	take_forks(t_info *info)
{
	pthread_mutex_lock(&info->philo->mutex);
	printf("thread %d has taken a fork\n", info->philo->i);
}

void	put_forks(t_info *info)
{
	pthread_mutex_unlock(&info->philo->mutex);
}

void	eat(t_info *info)
{
	sleep(info->philo->time_to_eat);
	printf("thread %d is eating\n", info->philo->i);
}

void	sleep_(t_info *info)
{
	sleep(info->philo->time_to_sleep);
	printf("thread %d is sleeping\n", info->philo->i);
}
