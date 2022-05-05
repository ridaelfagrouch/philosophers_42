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

static void	check_arg(int ac, char **av, enum e_erreur *exit_)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		check_is_digit(av[i], exit_);
		if (*exit_ == erreur_)
			return ;
		if (ft_atoi(av[i], exit_) == 0 || ft_atoi(av[i], exit_) < 0)
		{
			write(1, "error! arg no valid\n", 20);
			*exit_ = erreur_;
			return ;
		}
		if (*exit_ == erreur_)
			return ;
		i++;
	}
}

//*****************************************************************************

static void	initial_data(t_info *info, char **av, int ac, enum e_erreur *exit_)
{
	info->nmb_of_thread = ft_atoi(av[1], exit_);
	info->time_to_die = ft_atoi(av[2], exit_);
	info->time_to_eat = ft_atoi(av[3], exit_);
	info->time_to_sleep = ft_atoi(av[4], exit_);
	info->dead_statu = false;
	info->cont = 0;
	info->t0 = get_time();
	if (pthread_mutex_init(&info->print_mutex, NULL))
		*exit_ = erreur_;
	if (ac == 6)
		info->nmb_of_time_eat = ft_atoi(av[5], exit_);
	else
		info->nmb_of_time_eat = -1;
	if (*exit_ == erreur_)
		return ;
}

//*****************************************************************************

int	main(int ac, char *av[])
{
	t_info			info;
	enum e_erreur	exit_;

	exit_ = no_erreur_;
	if (ac > 6 || ac < 5)
	{
		write(2, "error\n", 6);
		return (0);
	}
	check_arg(ac, av, &exit_);
	if (exit_ == erreur_)
		return (0);
	initial_data(&info, av, ac, &exit_);
	if (exit_ == erreur_)
		return (0);
	creatlist(&info);
	creat_thread(&info, &exit_);
	if (exit_ == erreur_)
		return (0);
	check_dead(&info);
	detach_thread(&info);
	return (0);
}
