/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:50:30 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/07 22:41:48by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define GET_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>
# include <stdbool.h>

enum status
{
	LIVE,
	DIED
};

typedef struct s_philo_inf
{
	enum status		status;
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				eat_num;
	int				end_eat_flag;
	int				end_eat_num_to_finish;
}t_philo_inf;

typedef struct s_philos
{
	int				id;
	long			*last_eat_time;
	t_philo_inf		*info;
	struct s_philos	*left;
	struct s_philos	*right;
	pthread_mutex_t	mut_fork;
	pthread_mutex_t	mut_last_eat_time;
}t_philos;

/* main.c */
long		get_timestamp(void);
bool		check_philo_status(t_philos *philo);

/* validate.c */
bool		validate_args(int num, char **args);

/* init.c */
void		init_info_struct(t_philo_inf *info, int num, char **args);
t_philos	*create_philos_struct(int num);
void		init_philos_struct(t_philos *philos, t_philo_inf *inf);

/* philos_action.c */
void		print_philo_action(long timestamp, int id, char *action);
void		few_seconds_sleep(long after_time);
void		philo_eat(t_philos *philo);
void		philo_sleep(t_philos *philo);
void		philo_think(t_philos *philo);

/* get_forks.c */
void		get_first_fork(t_philos *philo);
void		get_second_fork(t_philos *philo);
void		get_forks(t_philos *philo);

/* put_forks.c */
void		put_first_fork(t_philos *philo);
void		put_second_fork(t_philos *philo);
void		put_forks(t_philos *philo);

/* utils */
int			ft_atoi(char *str);
bool		is_digit(char *arg);

/* output colors */
# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

#endif
