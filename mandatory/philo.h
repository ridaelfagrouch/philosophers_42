#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct philo_node
{
	pthread_t			th;
	pthread_mutex_t		mutex;
	int					index;
	int					nmb_of_eat;
	struct philo_node	*next;
	struct philo_node	*prev;
}	t_node;

typedef struct philo_info
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nmb_of_time_eat;
	int				i;
	t_node			*tmp;
	t_node			*newnode;
	pthread_mutex_t	*mutex;
	t_node			*thread;
}	t_philo;

typedef struct info
{
	t_node	*heade;
	t_node	*tail;
	t_philo	*philo;
}	t_info;

int		ft_atoi(const char *str);
void	check_is_digit(char *str);
void	take_forks(t_info	*info);
void	put_forks(t_info *info);
void	eat(t_info *info);
void	sleep_(t_info *info);

#endif