/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:33 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/03 15:27:42 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compile command */
//[$ ./philo 3 600 300 400 2]

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
	pthread_mutex_lock(&mut[first(id)]);
	printf("philosopher %d : get fork %d ... Done\n", id, first(id) + 1);
}

void	get_second_fork(int id)
{
	pthread_mutex_lock(&mut[second(id)]);
	printf("philosopher %d : get fork %d ... Done\n", id, second(id) + 1);
}

void	get_forks(int id)
{
	get_first_fork(id);
	get_second_fork(id);
}

void	put_first_fork(int id)
{
	pthread_mutex_unlock(&mut[first(id)]);
	printf("philosopher %d : put fork %d ... Done\n", id, first(id) + 1);
}

void	put_second_fork(int id)
{
	pthread_mutex_unlock(&mut[second(id)]);
	printf("philosopher %d : put fork %d ... Done\n", id, second(id) + 1);
}

void	put_forks(int id)
{
	put_first_fork(id);
	put_second_fork(id);
}

void	think(int id)
{
	printf("philosopher %d is thinking\n", id);
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
		exit(1);
	}
	printf("philosopher %d is eating\n", philo->id);
	usleep(inf.time_to_eat * 1000);
}

void	philo_sleep(int id)
{
	printf("philosopher %d is sleeping\n", id);
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
		think(philo->id);
		get_forks(philo->id);
		eat(philo);
		put_forks(philo->id);
		philo_sleep(philo->id);
		i += 1;
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
	philos = create_philos_struct(inf.philo_num - 1);//リストではなく普通に人数分をmallocで確保して配列で管理すればいいと思う
	init_philos_struct(philos, inf.philo_num);

	/* start program */
	pthread_t	*thread;
	int	i;
	mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * inf.philo_num);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * inf.philo_num);
	i = 0;
	while (i < inf.philo_num)
	{
		pthread_mutex_init(&mut[i], NULL);
		pthread_create(&thread[i], NULL, philosopher, philos);
		philos = philos->left;
		i += 1;
	}

	/* end thread */
	i = 0;
	while (i < inf.philo_num)
	{
		pthread_join(thread[i], NULL);
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
