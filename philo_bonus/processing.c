/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:58:04 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/09 14:58:10 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dead(void *info)
{
	int long	time_check;
	t_node		*node;
	t_info		*share;

	node = (t_node *) info;
	share = node->share;
	while (1)
	{
		time_check = get_time() - node->last_meal;
		if (time_check > share->time_to_die || \
			share->cont == share->nmb_of_thread)
		{
			if (time_check > share->time_to_die)
				print_messag(info, share->head, DEAD);
			share->dead_statu = true;
			exit(1);
		}
		if (node->nmb_of_eat == share->nmb_of_time_eat)
			share->cont++;
		usleep(100);
	}
	return (0);
}

//*****************************************************************************

void	ft_kill_process(t_info *info)
{
	int	i;

	i = 0;
	while (info->head)
	{
		kill(info->head->philo, SIGTERM);
		if (info->head->next == info->tmp)
			break ;
		info->head = info->head->next;
	}
}

//*****************************************************************************

void	_exit_process(t_info *info)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i < info->nmb_of_thread)
	{
		waitpid(-1, &exit_status, 0);
		if (exit_status != 0)
		{
			ft_kill_process(info);
			break ;
		}
	}
	sem_close(info->forks);
	sem_close(info->print_sem);
	sem_unlink("forks");
	sem_unlink("print_sem");
}

//*****************************************************************************

void	start_routine(t_info *info, t_node	*node)
{
	pthread_t	checkdead;

	node->last_meal = get_time();
	if (pthread_create(&checkdead, NULL, &check_dead, node))
	{
		write(2, "failed to create thread\n", 24);
		exit(1);
	}
	if (node->index % 2)
		usleep(100);
	while (info->dead_statu == false)
		routine(info, node);
	pthread_detach(checkdead);
}

//*****************************************************************************

void	processing(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nmb_of_thread)
	{
		info->head->philo = fork();
		if (info->head->philo < 0)
		{
			write(2, "error!\n", 7);
			exit(1);
		}
		if (info->head->philo == 0)
			start_routine(info, info->head);
		usleep(100);
		info->head = info->head->next;
		i++;
	}
	_exit_process(info);
}