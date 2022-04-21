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

void	*routine(void *info)
{
	t_info	result;

	result = *(t_info *)info;
	take_forks(result.tmp);
	// printf("hello from thread %d\n", result.tmp->index);
	// eat(info);
	put_forks(result.tmp);
	// sleep_(info);
	// think();
	return (NULL);
}

//*****************************************************************************

void	join_and_destroy(t_info *info)
{
	info->tmp = info->heade;
	while (info->tmp)
	{
		if (pthread_join(info->tmp->th, NULL) != 0)
			exit(1);
		info->tmp = info->tmp->next;
	}
	info->tmp = info->heade;
	while (info->tmp)
	{
		pthread_mutex_destroy(&info->tmp->mutex);
		info->tmp = info->tmp->next;
	}
}

//*****************************************************************************

void	initial_mutex(t_info *info)
{
	info->tmp = info->heade;
	while (info->tmp)
	{
		pthread_mutex_init(&info->tmp->mutex, NULL);
		info->tmp = info->tmp->next;
	}
}

//*****************************************************************************

void	creat_thread(t_info *info)
{
	initial_mutex(info);
	info->tmp = info->heade;
	while (info->tmp)
	{
		if (pthread_create(&info->tmp->th, NULL, &routine, &info) != 0)
		{
			write(2, "failed to create thread\n", 24);
			exit(1);
		}
		info->tmp = info->tmp->next;
	}
	join_and_destroy(info);
}

//*****************************************************************************

void	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		check_is_digit(av[i]);
		if (ft_atoi(av[i]) == 0 || ft_atoi(av[i]) < 0)
		{
			write(1, "error! arg no valid\n", 20);
			exit(1);
		}
		i++;
	}
}

//*****************************************************************************

void	initial_data(t_philo *philo, t_info *info, char **av, int ac)
{
	info->nmb_of_thread = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->nmb_of_time_eat = ft_atoi(av[5]);
	else
		info->nmb_of_time_eat = 0;
	philo->tmp = info->heade;
	philo->i = 0;
	while (philo->tmp)
	{
		philo->tmp->nmb_of_eat = 0;
		philo->tmp = philo->tmp->next;
	}
}

//*****************************************************************************

void	creat_list(t_info *info, t_philo *philo, char **av)
{
	philo->i = 0;
	while (philo->i < ft_atoi(av[1]))
	{
		philo->thread = (t_node *)malloc(sizeof(t_node));
		if (!philo->thread)
			exit(1);
		if (philo->i == 0)
		{
			philo->thread->next = NULL;
			philo->thread->prev = NULL;
			philo->thread->index = philo->i;
			info->heade = philo->thread;
			philo->tmp = info->heade;
		}
		else
		{
			philo->tmp->next = philo->thread;
			philo->thread->prev = philo->tmp;
			philo->thread->next = NULL;
			philo->thread->index = philo->i;
			philo->tmp = philo->tmp->next;
		}
		philo->i++;
	}
	info->tail = philo->thread;
}

//*****************************************************************************

void	print_list(t_info info)
{
	info.tmp = info.heade;
	printf("nb_of_thread = %d | t_t_die = %d | t_t_eat = %d | t_t_sleep = %d |\
 nb_of_t_eat = %d\n", \
		info.nmb_of_thread, info.time_to_die, info.time_to_eat, \
		info.time_to_sleep, info.nmb_of_time_eat);
	while (info.tmp)
	{
		printf("thread %d | nmb_of_eat = %d\n", \
			info.tmp->index, info.tmp->nmb_of_eat);
		info.tmp = info.tmp->next;
	}
}

//*****************************************************************************

int	main(int ac, char *av[])
{
	t_info	info;
	t_philo philo;

	if (ac == 6 || ac == 5)
	{
		check_arg(ac, av);
		creat_list(&info, &philo, av);
		initial_data(&philo, &info, av, ac);
		creat_thread(&info);
		// print_list(info);
	}
	else
	{
		write(2, "error\n", 6);
		exit(1);
	}
	return (0);
}
