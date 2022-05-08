/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:01:06 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/07 17:01:12 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_forks(t_info *info, t_node *node)
{
	pthread_mutex_lock(&node->fork);
	print_messag(info, node, TAKE_LEFT);
	pthread_mutex_lock(&node->next->fork);
	print_messag(info, node, TAKE_RIGHT);
}

//*****************************************************************************

static void	put_forks(t_node *node)
{
	pthread_mutex_unlock(&node->fork);
	pthread_mutex_unlock(&node->next->fork);
}

//*****************************************************************************

static void	start_routine(t_info *info, t_node *node)
{
	take_forks(info, node);
	print_messag(info, node, EAT);
	node->last_meal = get_time();
	ft_usleep(info->time_to_eat * 1000, info);
	node->nmb_of_eat++;
	if (node->nmb_of_eat == info->nmb_of_time_eat)
		info->cont++;
	put_forks(node);
	print_messag(info, node, SLEEP);
	ft_usleep(info->time_to_sleep * 1000, info);
	print_messag(info, node, THINK);
}

//*****************************************************************************

void	*routine(void *info)
{
	t_node		*node;
	t_info		*result;

	node = (t_node *)info;
	result = node->share;
	if (node->index % 2)
		usleep(100);
	while (result->dead_statu == false)
		start_routine(result, node);
	return (NULL);
}
