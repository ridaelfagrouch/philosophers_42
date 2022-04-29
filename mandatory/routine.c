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

static void	take_forks(t_info *info)
{
	if (info->node->index % 2 == 0)
	{
		pthread_mutex_lock(&info->node->mutex);
		print_messag(info, TAKE_LEFT);
		pthread_mutex_lock(&info->tmp->mutex);
		print_messag(info, TAKE_RIGHT);
	}
	else
	{
		ft_usleep(1000);
		pthread_mutex_lock(&info->node->mutex);
		print_messag(info, TAKE_LEFT);
		pthread_mutex_lock(&info->tmp->mutex);
		print_messag(info, TAKE_RIGHT);
	}
}

//*****************************************************************************

static void	put_forks(t_info *info)
{
	print_messag(info, PUT_LEFT);
	pthread_mutex_unlock(&info->node->mutex);
	print_messag(info, PUT_RIGHT);
	pthread_mutex_unlock(&info->tmp->mutex);
}

//*****************************************************************************

static void	check_node(t_info *info)
{
	if (info->node == info->heade)
		info->tmp = info->tail;
	else
		info->tmp = info->node->prev;
}

//*****************************************************************************

static void	start_routine(t_info *info)
{
	if (info->dead_statu == true || info->nmb_of_thread == 1)
	{
		print_messag(info, DEAD);
		exit(1);
	}
	check_node(info);
	take_forks(info);
	if ((get_time() - info->node->last_meal) > info->time_to_die && \
		(info->node->nmb_of_eat != 0))
			info->dead_statu = true;
	pthread_mutex_lock(&info->eat_mutex);
	print_messag(info, EAT);
	ft_usleep(info->time_to_eat * 1000);
	info->node->last_meal = get_time();
	info->node->nmb_of_eat++;
	pthread_mutex_unlock(&info->eat_mutex);
	put_forks(info);
	print_messag(info, THINK);
	print_messag(info, SLEEP);
	ft_usleep(info->time_to_sleep * 1000);
}

//*****************************************************************************

void	*routine(void *info)
{
	t_info	*result;

	result = (t_info *)info;
	while (1)
	{
		start_routine(result);
		if (result->node->nmb_of_eat == result->nmb_of_time_eat)
			break ;
	}
	return (NULL);
}
