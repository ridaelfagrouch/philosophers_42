/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:45:22 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/09 17:45:27 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_forks(t_info *info, t_node *node)
{
	sem_wait(info->forks);
	print_messag(info, node, TAKE_LEFT);
	sem_wait(info->forks);
	print_messag(info, node, TAKE_RIGHT);
}

//*****************************************************************************

static void	put_forks(t_info *info)
{
	sem_post(info->forks);
	sem_post(info->forks);
}

//*****************************************************************************

void	routine(t_info *info, t_node *node)
{
	take_forks(info, node);
	print_messag(info, node, EAT);
	node->last_meal = get_time();
	ft_usleep(info->time_to_eat * 1000, info);
	node->nmb_of_eat++;
	if (node->nmb_of_eat == info->nmb_of_time_eat)
		info->cont++;
	put_forks(info);
	print_messag(info, node, SLEEP);
	ft_usleep(info->time_to_sleep * 1000, info);
	print_messag(info, node, THINK);
}
