/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:33 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 17:04:27 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compile command */
//[$ ./philo 4 410 200 200 2]

#include "philosopher.h"

t_philo_inf	inf;

long	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("----- get time error! -----\n");
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	get_first_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->mut_fork);
	printf("%ld %d has taken a fork %d\n", get_timestamp(), philo->id, philo->id);
}

void	get_second_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->left->mut_fork);
	printf("%ld %d has taken a fork %d\n", get_timestamp(), philo->id, philo->left->id);
}

void	get_forks(t_philos *philo)
{
	get_first_fork(philo);
	get_second_fork(philo);
}

void	put_first_fork(t_philos *philo)
{
	pthread_mutex_unlock(&philo->mut_fork);
}

void	put_second_fork(t_philos *philo)
{
	pthread_mutex_unlock(&philo->left->mut_fork);
}

void	put_forks(t_philos *philo)
{
	put_first_fork(philo);
	put_second_fork(philo);
}

void	eat(t_philos *philo)
{
	pthread_mutex_lock(&(philo->mut_last_eat_time));
	*(philo->last_eat_time) = get_timestamp();
	pthread_mutex_unlock(&(philo->mut_last_eat_time));
	printf("%ld %d is eating\n", *(philo->last_eat_time), philo->id);
	usleep(inf.time_to_eat * 1000);
}

void	philo_sleep(t_philos *philo)
{
	printf("%ld %d is sleeping\n", get_timestamp(), philo->id);
	usleep(inf.time_to_sleep * 1000);
}

void	think(t_philos *philo)
{
	printf("%ld %d is thinking\n", get_timestamp(), philo->id);
}

void	*philosopher(void *arg)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)arg;
	i = 0;
	while (i < 5)//この条件はいずれ消す。終了は哲学者が死ぬか、任意の回数食事を終えるかのどちらかの場合。
	{
		get_forks(philo);
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);
		think(philo);
		i += 1;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philos	*philo;
	long		now;

	philo = (t_philos *)arg;
	while (philo->status == LIVE)
	{
		now = get_timestamp();
		pthread_mutex_lock(&(philo->mut_last_eat_time));
		if (now - *(philo->last_eat_time) >= inf.time_to_die)
		{
			philo->status = DEID;
			printf("%ld:%ld:%ld\n", now, *(philo->last_eat_time), now - *(philo->last_eat_time));
			printf("%ld %d died\n", now, philo->id);
		}
		pthread_mutex_unlock(&(philo->mut_last_eat_time));
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philos	*philos;

	/* validate and initialize */
	if(validate_args(argc - 1, argv) == false)
	{
		printf("The argument is incorrect.\n");
		return (1);
	}
	init_info_struct(&inf, argc - 1, argv);
	philos = create_philos_struct(inf.philo_num);
	init_philos_struct(philos, inf.philo_num);

	/* start program */
	pthread_t	*thread;
	int	i;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * (inf.philo_num * 2));
	i = 0;
	while (i < inf.philo_num)
	{
		pthread_create(&thread[i], NULL, philosopher, philos);
		pthread_create(&thread[i + inf.philo_num], NULL, monitor, philos);
		philos = philos->left;
		i += 1;
	}

	/* end thread */
	i = 0;
	while (i < inf.philo_num)
	{
		pthread_join(thread[i], NULL);
		pthread_detach(thread[i + inf.philo_num]);
		i += 1;
	}

	/* free philos, thread, mut */
	// i = 0;
	// while (i < inf.end_eat_num_to_finish)
	// {
		// free(mut[i]);
		// free(thread[i]);
		// free(philos[i]);
		// i += 1;
	// }

	printf("Finished!!!\n");
	return (0);
}
