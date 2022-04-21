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

void	take_forks(t_node *node)
{
	pthread_mutex_lock(&node->mutex);
	// printf("thread %d has taken a fork\n", info->philo->i);
}

void	put_forks(t_node *node)
{
	pthread_mutex_unlock(&node->mutex);
}

// void	eat(t_node *node)
// {
// 	sleep(info->philo->time_to_eat);
// 	printf("thread %d is eating\n", info->philo->i);
// }

// void	sleep_(t_node *node)
// {
// 	sleep(info->philo->time_to_sleep);
// 	printf("thread %d is sleeping\n", info->philo->i);
// }
