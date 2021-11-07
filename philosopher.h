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
	DEID
};

typedef struct s_philo_inf
{
	int		philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		end_eat_num_to_finish;
}t_philo_inf;

typedef struct s_philos
{
	t_philo_inf		*info;
	struct s_philos	*left;
	struct s_philos	*right;
	int				id;
	enum status		status;
	long			*last_eat_time;
	pthread_mutex_t	mut_fork;
	pthread_mutex_t	mut_last_eat_time;
}t_philos;

/* init.c */
bool		validate_args(int num, char **args);
void		init_info_struct(t_philo_inf *info, int num, char **args);
t_philos	*create_philos_struct(int num);
void		init_philos_struct(t_philos *philos, t_philo_inf *inf);

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

void		print_philo_action(long timestamp, int id, char *action);

long		get_timestamp(void);

#endif
