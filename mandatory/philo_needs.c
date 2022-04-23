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

void	start_routine(t_info *info)
{
	if (info->node == info->heade)
		info->tmp = info->tail;
	else
		info->tmp = info->node->prev;
	if (info->tmp->fork_statu == off && info->node->fork_statu == off)
	{
		pthread_mutex_lock(&info->node->mutex);
		pthread_mutex_lock(&info->tmp->mutex);
		info->node->fork_statu = on;
		info->tmp->fork_statu = on;
		printf("thread %d has take left fork\n", info->node->index);
		printf("thread %d has take right fork\n", info->node->index);
		printf("thread %d is eating\n", info->node->index);
		usleep(200);
		printf("thread %d has put left fork\n", info->node->index);
		printf("thread %d has put right fork\n", info->node->index);
		info->node->fork_statu = off;
		info->tmp->fork_statu = off;
		printf("thread %d is sleeping\n", info->node->index);
		printf("thread %d is think\n", info->node->index);
		pthread_mutex_unlock(&info->node->mutex);
		pthread_mutex_unlock(&info->tmp->mutex);
	}
}
