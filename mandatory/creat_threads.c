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
	if (result->node->nmb_of_eat == 0)
	{
		pthread_mutex_lock(&result->node->mutex);
		printf("id = %d | nmb_of_eat = %d\n", result->node->index, result->node->nmb_of_eat);
		result->node->nmb_of_eat++;
		pthread_mutex_unlock(&result->node->mutex);
	}
	// while (1)
	// {
	// 	take_forks(&result);
	// 	eat(info);
	// 	put_forks(&result);
	// 	sleep_(info);
	// 	think();
	// }
	return (NULL);
}

//*****************************************************************************

static void	join_(t_info *info)
{
	info->node = info->heade;
	while (info->node)
	{
		if (pthread_join(info->node->th, NULL) != 0)
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
		if (pthread_create(&info->node->th, NULL, &routine, info) != 0)
		{
			write(2, "failed to create thread\n", 24);
			exit(1);
		}
		info->node = info->node->next;
	}
	join_(info);
}
