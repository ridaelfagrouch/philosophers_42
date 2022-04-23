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
	if (ac == 6)
		info->nmb_of_time_eat = ft_atoi(av[5]);
	else
		info->nmb_of_time_eat = 0;
	info->tmp = info->heade;
	info->i = 0;
	while (info->tmp)
	{
		info->tmp->nmb_of_eat = 0;
		info->tmp = info->tmp->next;
	}
}

//*****************************************************************************

void	first_node_data(t_info *info)
{
	info->node->next = NULL;
	info->node->prev = NULL;
	info->node->index = info->i;
	info->node->fork_statu = off;
	info->node->last_meal = 0;
	info->heade = info->node;
	info->tmp = info->heade;
}

static void	creat_list(t_info *info, char **av)
{
	info->i = 0;
	while (info->i < ft_atoi(av[1]))
	{
		info->node = (t_node *)malloc(sizeof(t_node));
		if (!info->node)
			exit(1);
		if (info->i == 0)
			first_node_data(info);
		else
		{
			info->tmp->next = info->node;
			info->node->prev = info->tmp;
			info->node->next = NULL;
			info->node->index = info->i;
			info->node->fork_statu = off;
			info->node->last_meal = 0;
			info->tmp = info->tmp->next;
		}
		info->i++;
	}
	info->tail = info->node;
}

//*****************************************************************************

// void	print_list(t_info info)
// {
// 	info.node = info.heade;
// 	printf("nb_of_thread = %d | t_t_die = %d | t_t_eat = %d | t_t_sleep = %d |\
//  nb_of_t_eat = %d\n", \
// 		info.nmb_of_thread, info.time_to_die, info.time_to_eat, \
// 		info.time_to_sleep, info.nmb_of_time_eat);
// 	while (info.node)
// 	{
// 		printf("thread %d | nmb_of_eat = %d | fork_statu = %d | fork_number = %d\n", \
// 			info.node->index, info.node->nmb_of_eat, info.node->fork_statu, info.node->fork_number);
// 		info.node = info.node->next;
// 	}
// }

//*****************************************************************************

int	main(int ac, char *av[])
{
	t_info	info;

	if (ac > 6 || ac < 5)
	{
		write(2, "error\n", 6);
		exit(1);
	}
	check_arg(ac, av);
	creat_list(&info, av);
	initial_data(&info, av, ac);
	creat_thread(&info);
	// print_list(info);
	return (0);
}
