/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:46:52 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/04/22 11:46:55 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *info)
{
	t_info	*result;

	result = (t_info *)info;
	while (1)
		start_routine(result);
	return (NULL);
}

//*****************************************************************************

static void	initial_mutex(t_info *info)
{
	info->node = info->heade;
	while (info->node)
	{
		if (pthread_mutex_init(&info->node->mutex, NULL))
			exit(1);
		info->node = info->node->next;
	}
}

//*****************************************************************************

static t_info	*clone_info(t_info *info)
{
	t_info	*new_info;

	new_info = (t_info *)malloc(sizeof(t_info));
	if (!new_info)
		exit(1);
	new_info->heade = info->heade;
	new_info->tail = info->tail;
	new_info->node = info->node;
	new_info->tmp = info->tmp;
	new_info->i = info->i;
	new_info->t0 = info->t0;
	new_info->cont_eat = info->cont_eat;
	new_info->time_to_die = info->time_to_die;
	new_info->time_to_eat = info->time_to_eat;
	new_info->time_to_sleep = info->time_to_sleep;
	new_info->nmb_of_time_eat = info->nmb_of_time_eat;
	new_info->nmb_of_thread = info->nmb_of_thread;
	return (new_info);
}

//*****************************************************************************

static void	join_(t_info *info)
{
	info->node = info->heade;
	while (info->node)
	{
		if (pthread_join(info->node->thread, NULL))
			exit(1);
		info->node = info->node->next;
	}
}

//*****************************************************************************

void	creat_thread(t_info *info)
{
	initial_mutex(info);
	info->node = info->heade;
	while (info->node)
	{
		usleep(1000);
		if (pthread_create(&info->node->thread, NULL, &routine, \
			clone_info(info)))
		{
			write(2, "failed to create thread\n", 24);
			exit(1);
		}
		info->node = info->node->next;
	}
	join_(info);
}
