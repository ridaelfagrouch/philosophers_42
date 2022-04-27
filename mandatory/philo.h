#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

enum e_fork{off, on};
enum e_dead{fols, true};

typedef struct philo_node
{
	struct philo_node	*next;
	struct philo_node	*prev;
	long int			last_meal;
	int					index;
	int					nmb_of_eat;
	pthread_t			thread;
	enum e_fork			fork_statu;
	pthread_mutex_t		mutex;
}	t_node;

typedef struct info
{
	t_node		*heade;
	t_node		*tail;
	t_node		*node;
	t_node		*tmp;
	enum e_dead	dead_statu;
	int			i;
	long int	t0;
	int			cont_eat;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nmb_of_time_eat;
	int			nmb_of_thread;
}	t_info;

int		ft_atoi(const char *str);
void	check_is_digit(char *str);
size_t	ft_strlen(const char *str);
void	creat_thread(t_info *info);
void	start_routine(t_info *info);
long	get_time(void);

#endif