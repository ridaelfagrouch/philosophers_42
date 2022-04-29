#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_LEFT	0
# define TAKE_RIGHT	1
# define EAT	2
# define DEAD	3
# define PUT_LEFT	4
# define PUT_RIGHT	5
# define SLEEP	6
# define THINK	7

enum e_dead{false, true};

typedef struct philo_node
{
	struct philo_node	*next;
	struct philo_node	*prev;
	long int			last_meal;
	int					index;
	int					nmb_of_eat;
	pthread_t			thread;
	pthread_mutex_t		mutex;
}	t_node;

typedef struct info
{
	t_node				*heade;
	t_node				*tail;
	t_node				*node;
	t_node				*tmp;
	enum e_dead			dead_statu;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		print_mutex;
	long int			t0;
	int					i;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nmb_of_time_eat;
	int					nmb_of_thread;
}	t_info;

int		ft_atoi(const char *str);
void	check_is_digit(char *str);
size_t	ft_strlen(const char *str);
void	creat_thread(t_info *info);
long	get_time(void);
void	ft_usleep(long int time);
void	*routine(void *info);
void	print_messag(t_info *info, int key);

#endif