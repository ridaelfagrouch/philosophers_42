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

void	check_dead(t_info *info)
{
	int long	time_check;

	while (info->head)
	{
		time_check = get_time() - info->head->last_meal;
		if (time_check > info->time_to_die || \
			info->cont == info->nmb_of_thread)
		{
			if (time_check > info->time_to_die)
				print_messag(info, info->head, DEAD);
			info->dead_statu = true;
			return ;
		}
		usleep(1000);
		info->head = info->head->next;
	}
}

//*****************************************************************************

void	detach_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nmb_of_thread)
	{
		pthread_detach(info->head->thread);
		pthread_mutex_destroy(&info->head->fork);
		info->tmp = info->head;
		info->head = info->head->next;
		free(info->tmp);
		i++;
	}
	pthread_mutex_destroy(&info->print_mutex);
	return ;
}

//*****************************************************************************

void	creat_thread(t_info *info, enum e_erreur *exit_)
{
	while (info->head)
	{
		if (pthread_create(&info->head->thread, NULL, &routine, info->head))
		{
			write(2, "failed to create thread\n", 24);
			*exit_ = erreur_;
			return ;
		}
		info->head->last_meal = get_time();
		if (info->head->next == info->tmp)
			break ;
		info->head = info->head->next;
	}
}
