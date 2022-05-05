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

static void	check_arg(int ac, char **av)
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

static void	initial_data(t_info *info, char **av, int ac)
{
	info->nmb_of_thread = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->dead_statu = false;
	info->cont = 0;
	info->t0 = get_time();
	if (pthread_mutex_init(&info->print_mutex, NULL))
		exit(1);
	if (ac == 6)
		info->nmb_of_time_eat = ft_atoi(av[5]);
	else
		info->nmb_of_time_eat = -1;
	creatlist(info);
}

//*****************************************************************************

// void	print_list(t_info *info)
// {
// 	printf("dead_stat : %d | t0 : %ld | cont : %d | t_to_die : %d | \
// t_to_eat : %d | t_to_sleep : %d | nmb_of_eat : %d | nmb_of_philo : %d \n", \
// 		info->dead_statu, info->t0, info->cont, info->time_to_die, info->time_to_eat, \
// 		info->time_to_sleep, info->nmb_of_time_eat, info->nmb_of_thread);
// 	while (info->head)
// 	{
// 		printf("lst_meal : %ld | index : %d | nmb_of_eat : %d\n", \
// 			info->head->last_meal, info->head->index, info->head->nmb_of_eat);
// 		if (info->head->next == info->tmp)
// 			break ;
// 		info->head = info->head->next;
// 	}
// }

int	main(int ac, char *av[])
{
	t_info	info;

	if (ac > 6 || ac < 5)
	{
		write(2, "error\n", 6);
		exit(1);
	}
	check_arg(ac, av);
	initial_data(&info, av, ac);
	creat_thread(&info);
	check_dead(&info);
	detach_thread(&info);
	return (0);
}
