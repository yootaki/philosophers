/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:33 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/03 18:08:46 yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compile command */
//[$ ./philo 3 600 300 200 2]

#include "philosopher.h"

t_philo_inf		inf;
pthread_mutex_t	*mut;

int	first(int id)
{
	return (id - 1);
}

int	second(int id)
{
	return (id % inf.philo_num);
}

void	get_first_fork(int id)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("get time error!\n");
	}
	pthread_mutex_lock(&mut[first(id)]);
	printf("%ld%d %d : get fork %d ... Done\n", tv.tv_sec, (tv.tv_usec / 1000), id, first(id) + 1);
}

void	get_second_fork(int id)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("get time error!\n");
	}
	pthread_mutex_lock(&mut[second(id)]);
	printf("%ld%d %d : get fork %d ... Done\n", tv.tv_sec, (tv.tv_usec / 1000), id, second(id) + 1);
}

void	get_forks(int id)
{
	get_first_fork(id);
	get_second_fork(id);
}

void	put_first_fork(int id)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("get time error!\n");
	}
	pthread_mutex_unlock(&mut[first(id)]);
	printf("%ld%d %d : put fork %d ... Done\n", tv.tv_sec, (tv.tv_usec / 1000), id, first(id) + 1);
}

void	put_second_fork(int id)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("get time error!\n");
	}
	pthread_mutex_unlock(&mut[second(id)]);
	printf("%ld%d %d : put fork %d ... Done\n", tv.tv_sec, (tv.tv_usec / 1000), id, second(id));
}

void	put_forks(int id)
{
	put_first_fork(id);
	put_second_fork(id);
}

void	think(int id)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("get time error!\n");
	}
	printf("%ld%d %d is thinking\n", tv.tv_sec, (tv.tv_usec / 1000), id);
	if (id % 2 == 1)
	{
		usleep(200);
	}
}

void	eat(t_philos *philo)
{
	if (gettimeofday(&(philo->last_eat_time), NULL))
	{
		printf("get time error!\n");
	}
	printf("%ld%d %d is eating\n", philo->last_eat_time.tv_sec, (philo->last_eat_time.tv_usec / 1000), philo->id);
	usleep(inf.time_to_eat * 1000);
}

void	philo_sleep(int id)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("get time error!\n");
	}
	printf("%ld%d %d is sleeping\n", tv.tv_sec, (tv.tv_usec / 1000), id);
	usleep(inf.time_to_sleep * 1000);
}

void	*philosopher(void *arg)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)arg;
	i = 0;
	while (i < 5)//この条件はいずれ消す。終了は哲学者が死ぬか、任意の回数食事を終えるかのどちらかの場合。
	{
		get_forks(philo->id);
		eat(philo);
		put_forks(philo->id);
		philo_sleep(philo->id);
		think(philo->id);
		i += 1;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philos		*philo;
	struct timeval	now;

	philo = (t_philos *)arg;
	while (philo->status == LIVE)
	{
		if (gettimeofday(&now, NULL))
		{
			printf("get time error!\n");
		}
		if ((now.tv_usec / 1000) - (philo->last_eat_time.tv_usec / 1000) >= inf.time_to_die)
		{
			philo->status = DEID;
			printf("%ld%d %d died\n", now.tv_sec, (now.tv_usec / 1000), philo->id);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philos	*philos;

	/* validate and initialize */
	if(validate_args(argc - 1, argv) == false)
	{
		return (1);
	}
	init_info_struct(&inf, argc - 1, argv);
	philos = (t_philos *)malloc(sizeof(t_philos) * inf.philo_num);
	init_philos_struct(philos, inf.philo_num);

	/* start program */
	pthread_t	*thread;
	int	i;
	mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * inf.philo_num);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * (inf.philo_num * 2));
	i = 0;
	while (i < inf.philo_num)
	{
		pthread_mutex_init(&mut[i], NULL);
		pthread_create(&thread[i], NULL, philosopher, &philos[i]);
		pthread_create(&thread[i + inf.philo_num], NULL, monitor, &philos[i]);
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
