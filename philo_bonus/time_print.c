/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:15:28 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/08 15:15:54 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(long int time_us, t_info *info)
{
	if (info->dead_statu == false)
		usleep(time_us);
}

//*****************************************************************************

long	get_time(void)
{
	struct timeval	current_time;
	long int		time_exact;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		write(2, "error! gettimeofday\n", 20);
		return (0);
	}
	time_exact = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time_exact);
}

//*****************************************************************************

void	print_messag(t_info *info, t_node *node, int key)
{
	long int	time;

	sem_wait(info->print_sem);
	if (info->dead_statu == false)
	{
		time = get_time() - info->t0;
		if (key == TAKE_LEFT)
			printf("%ld ms| %d has take left fork\n", time, node->index);
		else if (key == TAKE_RIGHT)
			printf("%ld ms| %d has take right fork\n", time, node->index);
		else if (key == SLEEP)
			printf("%ld ms| %d is sleeping\n", time, node->index);
		else if (key == THINK)
			printf("%ld ms| %d is think\n", time, node->index);
		else if (key == EAT)
			printf("%ld ms| %d is eating\n", time, node->index);
		else if (key == DEAD)
			printf("%ld ms| %d is dead\n", time, node->index);
	}
	sem_post(info->print_sem);
}