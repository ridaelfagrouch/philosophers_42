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

static void	join_(t_info *info)
{
	info->node = info->heade;
	while (info->node)
	{
		if (pthread_join(info->node->thread, NULL) != 0)
			exit(1);
		info->node = info->node->next;
	}
}

//*****************************************************************************

static void	initial_mutex(t_info *info)
{
	info->node = info->heade;
	while (info->node)
	{
		pthread_mutex_init(&info->node->mutex, NULL);
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
		if (pthread_create(&info->node->thread, NULL, &routine, info) != 0)
		{
			write(2, "failed to create thread\n", 24);
			exit(1);
		}
		// pthread_detach(info->node->thread);
		usleep(100);
		info->node = info->node->next;
	}
	join_(info);
}
