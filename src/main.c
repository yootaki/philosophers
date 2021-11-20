/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:33 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 23:13:37y yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdbool.h>

/* Function to get a timestamp and convert it to milliseconds and return it. */
long	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("----- get time error! -----\n");
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_philo_action(long timestamp, int id, char *action)
{
	printf("%ld %d %s\n", timestamp, id, action);
}

/* Function to sleep until a after_time. */
void	few_seconds_sleep(long after_time)
{
	long	now;

	now = get_timestamp();
	while (1)
	{
		usleep(1000);
		now = get_timestamp();
		if (now >= after_time)
		{
			break ;
		}
	}
}

/* Update the last time you ate and wait for an arbitrary number of seconds. */
void	eat(t_philos *philo)
{
	pthread_mutex_lock(&(philo->mut_last_eat_time));
	philo->info->eat_num += 1;
	*(philo->last_eat_time) = get_timestamp();
	pthread_mutex_unlock(&(philo->mut_last_eat_time));
	print_philo_action(*(philo->last_eat_time), philo->id, EAT);
	few_seconds_sleep(*(philo->last_eat_time) + philo->info->time_to_eat);
}

/* Wait for an arbitrary number of seconds. */
void	philo_sleep(t_philos *philo)
{
	long	time;

	time = get_timestamp();
	print_philo_action(time, philo->id, SLEEP);
	few_seconds_sleep(time + philo->info->time_to_sleep);
}

void	think(t_philos *philo)
{
	print_philo_action(get_timestamp(), philo->id, THINK);
}

bool	check_philo_status(t_philos *philo)
{
	if (philo->info->status == DIED)
	{
		return (false);
	}
	else if (philo->info->end_eat_flag == 1 && \
			philo->info->eat_num >= philo->info->end_eat_num_to_finish)
	{
		return (false);
	}
	return (true);
}

/* Monitor the philosopher's status and flag any deaths. */
void	*monitor(void *arg)
{
	t_philos	*philo;
	long		now;
	long		last;

	philo = (t_philos *)arg;
	while (check_philo_status(philo))
	{
		now = get_timestamp();
		pthread_mutex_lock(&(philo->mut_last_eat_time));
		last = *(philo->last_eat_time);
		if (now - last >= philo->info->time_to_die)
		{
			philo->info->status = DIED;
			// printf("%ld:%ld:%ld\n", now, last, philo->info->time_to_die);
			printf("\x1b[31m%ld %d died\x1b[39m\n", now, philo->id);
		}
		pthread_mutex_unlock(&(philo->mut_last_eat_time));
		usleep(100);
	}
	return (NULL);
}

/* Continue the process until the philosopher is dead. */
void	*philosopher(void *arg)
{
	t_philos	*philo;
	pthread_t	thread;

	philo = (t_philos *)arg;
	pthread_create(&thread, NULL, monitor, philo);
	while (check_philo_status(philo))
	{
		get_forks(philo);
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);
		think(philo);
	}
	pthread_join(thread, NULL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo_inf	info;
	t_philos	*philos;

	/* validate and initialize */
	if(validate_args(argc - 1, argv) == false)
	{
		printf("The argument is incorrect.\n");
		return (1);
	}
	init_info_struct(&info, argc - 1, argv);
	philos = create_philos_struct(info.philo_num);
	init_philos_struct(philos, &info);

	/* start program */
	pthread_t	*thread;
	int	i;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * info.philo_num);
	i = 0;
	while (i < info.philo_num)
	{
		pthread_create(&thread[i], NULL, philosopher, philos);
		philos = philos->left;
		i += 1;
	}
	i = 0;
	while (i < info.philo_num)
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}

	/* free philos, thread, mut and destroy mutex*/
	//リークしないようfreeすること

	printf("Finished!!!\n");
	return (0);
}
