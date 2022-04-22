#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

enum e_fork{off, on};

typedef struct philo_node
{
	pthread_t			thread;
	enum e_fork			fork_statu;
	int					fork_number;
	int					last_meal;
	pthread_mutex_t		mutex;
	int					index;
	int					nmb_of_eat;
	struct philo_node	*next;
	struct philo_node	*prev;
}	t_node;

typedef struct info
{
	t_node	*heade;
	t_node	*tail;
	t_node	*node;
	t_node	*tmp;
	t_node	*tmp1;
	int		i;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nmb_of_time_eat;
	int		nmb_of_thread;
}	t_info;

int		ft_atoi(const char *str);
void	check_is_digit(char *str);
size_t	ft_strlen(const char *str);
void	creat_thread(t_info *info);
void	take_forks(t_info *info);
void	put_forks(t_info *info);

#endif