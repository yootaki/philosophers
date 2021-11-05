/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:50:30 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/04 17:19:53 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	end_eat_num_to_finish;
}t_philo_inf;

typedef struct s_philos
{
	struct s_philos	*left;
	struct s_philos	*right;
	int				id;
	enum status		status;
	long			*last_eat_time;
	pthread_mutex_t	mut_fork;
	pthread_mutex_t	mut_last_eat_time;
}t_philos;

/* init.c */
bool		is_digit(char *arg);
bool		validate_args(int num, char **args);
void		init_info_struct(t_philo_inf *inf, int num, char **args);
t_philos	*create_philos_struct(int num);
void		init_philos_struct(t_philos *philos, int num);

/* utils */
int			ft_atoi(char *str);

long		get_timestamp(void);

#endif
