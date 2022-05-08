/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:00:21 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/07 17:00:26 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_list(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nmb_of_thread)
	{
		info->tmp = info->head;
		info->head = info->head->next;
		free(info->tmp);
		i++;
	}
}

//*****************************************************************************

static void	check_arg(int ac, char **av, t_erreur *isexit)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		check_is_digit(av[i], isexit);
		if (*isexit == yes)
			return ;
		if (ft_atoi(av[i], isexit) == 0 || ft_atoi(av[i], isexit) < 0)
		{
			write(1, "error! arg no valid\n", 20);
			*isexit = yes;
			return ;
		}
		if (*isexit == yes)
			return ;
		i++;
	}
}

//*****************************************************************************

static void	initial_data(t_info *info, char **av, int ac, t_erreur *isexit)
{
	info->nmb_of_thread = ft_atoi(av[1], isexit);
	info->time_to_die = ft_atoi(av[2], isexit);
	info->time_to_eat = ft_atoi(av[3], isexit);
	info->time_to_sleep = ft_atoi(av[4], isexit);
	info->dead_statu = false;
	info->cont = 0;
	info->t0 = get_time();
	if (pthread_mutex_init(&info->print_mutex, NULL))
		*isexit = yes;
	if (ac == 6)
		info->nmb_of_time_eat = ft_atoi(av[5], isexit);
	else
		info->nmb_of_time_eat = -1;
	if (*isexit == yes)
		return ;
}

//*****************************************************************************

static void	check_init_creat(int ac, char **av, t_info *info, t_erreur *isexit)
{
	check_arg(ac, av, isexit);
	if (*isexit == yes)
		return ;
	initial_data(info, av, ac, isexit);
	if (*isexit == yes)
		return ;
	creatlist(info, isexit);
	if (*isexit == yes)
	{
		free_list(info);
		return ;
	}
}

//*****************************************************************************

int	main(int ac, char *av[])
{
	t_info			info;
	t_erreur		isexit;

	isexit = no;
	if (ac > 6 || ac < 5)
	{
		write(2, "error\n", 6);
		return (0);
	}
	check_init_creat(ac, av, &info, &isexit);
	if (isexit == yes)
		return (0);
	// creat_thread(&info, &isexit);
	// if (isexit == yes)
	// {
	// 	detach_thread(&info);
	// 	return (0);
	// }
	// check_dead(&info);
	// detach_thread(&info);
	return (0);
}
