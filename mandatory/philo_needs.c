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

void	take_forks(t_info	*info)
{
	info->tmp = info->node;
	if (info->node == info->heade)
	{
		info->tmp = info->tmp->next;
		info->tmp1 = info->tail;
	}
	else if (info->node == info->tail)
	{
		info->tmp = info->node->prev;
		info->tmp1 = info->heade;
	}
	else
	{
		info->tmp = info->node->prev;
		info->tmp1 = info->node->next;
	}
	if (info->tmp->fork_statu == off && info->tmp1->fork_statu == off)
	{
		pthread_mutex_lock(&info->tmp->mutex);
		printf("thread %d has take left fork\n", info->node->index);
		pthread_mutex_lock(&info->tmp1->mutex);
		printf("thread %d has take right fork\n", info->node->index);
		info->node->fork_number += 2;
		info->tmp->fork_statu = on;
		info->tmp1->fork_statu = on;
	}
}

void	put_forks(t_info *info)
{
	info->tmp = info->node;
	if (info->node == info->heade)
	{
		info->tmp = info->tmp->next;
		info->tmp1 = info->tail;
	}
	else if (info->node == info->tail)
	{
		info->tmp = info->node->prev;
		info->tmp1 = info->heade;
	}
	else
	{
		info->tmp = info->node->prev;
		info->tmp1 = info->node->next;
	}
	if (info->tmp->fork_statu == on && info->tmp1->fork_statu == on)
	{
		pthread_mutex_unlock(&info->tmp->mutex);
		printf("thread %d has put left fork\n", info->node->index);
		pthread_mutex_unlock(&info->tmp1->mutex);
		printf("thread %d has put right fork\n", info->node->index);
		info->node->fork_number -= 2;
		info->tmp->fork_statu = off;
		info->tmp1->fork_statu = off;
	}
}

void	eat(t_info *info)
{
	sleep(info->time_to_eat);
	printf("thread %d is eating\n", info->node->index);
}

// void	sleep_(t_node *node)
// {
// 	sleep(info->philo->time_to_sleep);
// 	printf("thread %d is sleeping\n", info->philo->i);
// }
