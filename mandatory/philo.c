/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:48:25 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/04/18 21:48:28 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//*****************************************************************************

void	*start_philo(void *share)
{
	// t_share	*result;

	// result = (t_share *)malloc(sizeof(t_share));
	// if (!result)
	// 	exit(1);
	take_forks(share);
	eat(share);
	put_forks(share);
	sleep_(share);
	think();
	return (NULL);
}

//*****************************************************************************

void	initial_data(t_info *info, char **av, int ac)
{
	int	i;

	i = 2;
	while (i < ac)
	{
		check_is_digit(av[i]);
		i++;
	}
	if (ac == 5)
		info->philo->nmb_of_time_eat = 0;
	else
		info->philo->nmb_of_time_eat = ft_atoi(av[5]);
	info->philo->time_to_die = ft_atoi(av[2]);
	info->philo->time_to_eat = ft_atoi(av[3]);
	info->philo->time_to_sleep = ft_atoi(av[4]);
	while (info->philo->i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&info->philo->mutex[info->philo->i], NULL);
		info->philo->i++;
	}
	info->philo->i = 0;
	info->philo->thread->index = info->philo->i;
	info->philo->thread->mutex = info->philo->mutex[info->philo->i];
	info->philo->tmp = info->philo->thread;
}

//*****************************************************************************

void	newnode_data(t_info *info)
{
	info->philo->newnode->index = info->philo->i + 1;
	info->philo->newnode->mutex = info->philo->mutex[info->philo->i + 1];
	info->philo->newnode->next = NULL;
	if (info->philo->i != 0)
		info->philo->newnode->prev = info->philo->tmp;
}

//*****************************************************************************

void	join_and_destroy(t_info *info)
{
	info->philo->tmp = info->heade;
	while (info->philo->tmp)
	{
		if (pthread_join(info->philo->tmp->th, NULL) != 0)
			exit(1);
		info->philo->tmp = info->philo->tmp->next;
	}
	info->philo->tmp = info->heade;
	while (info->philo->tmp)
	{
		pthread_mutex_destroy(&info->philo->tmp->mutex);
		info->philo->tmp = info->philo->tmp->next;
	}
}

//*****************************************************************************

void	creat_thread(t_info *info, char **av, int ac)
{
	info->philo->i = 0;
	initial_data(info, av, ac);
	while (info->philo->i < ft_atoi(av[1]))
	{
		if (pthread_create(&info->philo->tmp->th, NULL, &start_philo, &info) != 0)
		{
			write(2, "failed to create thread\n", 24);
			exit(1);
		}
		info->philo->newnode = (t_node *)malloc(sizeof(t_node));
		if (!info->philo->newnode)
			exit(1);
		if (info->philo->i == 0)
		{
			info->philo->thread->next = info->philo->newnode;
			info->philo->thread->prev = NULL;
			info->philo->newnode->prev = info->philo->thread;
		}
		newnode_data(info);
		info->philo->tmp = info->philo->newnode;
		info->philo->i++;
	}
	info->tail = info->philo->newnode;
	join_and_destroy(info);
}

//*****************************************************************************

int	main(int ac, char *av[])
{
	t_info	info;

	if (ac == 6 || ac == 5)
	{
		check_is_digit(av[1]);
		info.philo->thread = (t_node *)malloc(sizeof(t_node));
		if (!info.philo->thread)
			exit(1);
		info.philo->mutex = (pthread_mutex_t *) \
			malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
		if (!info.philo->mutex)
			exit(1);
		info.heade = info.philo->thread;
		info.tail = info.philo->thread;
		creat_thread(&info, av, ac);
	}
	else
	{
		write(2, "error\n", 6);
		exit(1);
	}
	return (0);
}
