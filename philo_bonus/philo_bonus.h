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
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <semaphore.h>

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
	pid_t				philo;
	long int			last_meal;
	int					index;
	int					nmb_of_eat;
	struct s_info		*share;
}	t_node;

typedef struct s_info
{
	t_node				*head;
	t_node				*tmp;
	t_dead				dead_statu;
	sem_t				*print_sem;
	sem_t				*forks;
	long int			t0;
	t_erreur			isexit;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nmb_of_time_eat;
	int					nmb_of_thread;
}	t_info;

int		ft_atoi(const char *str, t_erreur *exit_);
void	check_is_digit(char *str, t_erreur *exit_);
size_t	ft_strlen(const char *str);
long	get_time(void);
void	creatlist(t_info *info, t_erreur *isexit);
void	processing(t_info *info);
void	print_messag(t_info *info, t_node *node, int key);
long	get_time(void);
void	ft_usleep(long int time_us, t_info *info);
void	routine(t_info *info, t_node *node);
void	free_list(t_info *info);

#endif
