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

enum e_status
{
	CONTINUE,
	FINISH
};

enum e_threads
{
	PHILO,
	MONITOR,
	NUM
};

typedef struct s_philo_info
{
	enum e_status	status;
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				end_eat_num_to_finish;
	bool			end_eat_flag;
	pthread_mutex_t	mut_action;
}t_philo_info;

typedef struct s_philos
{
	t_philo_info	*info;
	struct s_philos	*left;
	struct s_philos	*right;
	int				id;
	int				eat_num;
	long			last_eat_time;
	pthread_mutex_t	mut_fork;
}t_philos;

/* check_status.c */
bool		check_philo_status(t_philos *philo);
void		check_philo_life(t_philos *philo);
void		check_philo_eatnum(t_philos *philo);

/* thread.c */
void		*monitor(void *arg);
void		*philosopher(void *arg);
bool		launch_thread(t_philos *philos, \
							pthread_t *thread, \
							void*(*func)(void*));
void		join_all_thread(int philo_num, pthread_t **thread);

/* validate.c */
bool		validate_args(int num, char **args);

/* init.c */
void		init_info_struct(t_philo_info *info, int argc, char **args);
bool		create_philos_struct(int philo_num, t_philos **philos);
bool		create_threads(int philo_num, pthread_t **thread);
void		init_philos_struct(t_philos *philos, t_philo_info *inf);

/* get_timestamp.c */
long		get_timestamp(void);

/* philos_action.c */
void		print_philo_action(long timestamp, int id, char *action);
void		few_seconds_sleep(long after_time);
bool		philo_eat(t_philos *philo);
bool		philo_sleep(t_philos *philo);
bool		philo_think(t_philos *philo);

/* get_forks.c */
bool		get_right_fork(t_philos *philo);
bool		get_left_fork(t_philos *philo);
bool		get_forks(t_philos *philo);

/* put_forks.c */
bool		put_right_fork(t_philos *philo);
bool		put_left_fork(t_philos *philo);
bool		put_forks(t_philos *philo);

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
