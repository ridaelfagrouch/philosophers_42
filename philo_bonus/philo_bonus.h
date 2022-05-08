/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:00:44 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/07 17:00:49 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_LEFT	0
# define TAKE_RIGHT	1
# define EAT	2
# define DEAD	3
# define SLEEP	6
# define THINK	7

typedef enum dead{false, true}	t_dead;
typedef enum erreur{no, yes}	t_erreur;

typedef struct philo_node
{
	struct philo_node	*next;
	long int			last_meal;
	int					index;
	int					nmb_of_eat;
	pthread_t			thread;
	pthread_mutex_t		fork;
	struct s_info		*share;
}	t_node;

typedef struct s_info
{
	t_node				*head;
	t_node				*tmp;
	t_dead				dead_statu;
	pthread_mutex_t		print_mutex;
	long int			t0;
	int					cont;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nmb_of_time_eat;
	int					nmb_of_thread;
}	t_info;

int		ft_atoi(const char *str, t_erreur *exit_);
void	check_is_digit(char *str, t_erreur *exit_);
size_t	ft_strlen(const char *str);
void	creat_thread(t_info *info, t_erreur *exit_);
long	get_time(void);
void	ft_usleep(long int time, t_info *info);
void	*routine(void *info);
void	print_messag(t_info *info, t_node *node, int key);
void	detach_thread(t_info *info);
void	creatlist(t_info *info, t_erreur *isexit);
void	check_dead(t_info *info);

#endif
