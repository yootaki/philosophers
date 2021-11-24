/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:10:17 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/24 16:23:22 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		pthread_mutex_lock(&(philo->info->mut_action));
		last = philo->last_eat_time;
		if (now - last >= philo->info->time_to_die)
		{
			philo->info->status = FINISH;
			printf("%s%ld %d died%s\n", RED, now, philo->id, RESET);
		}
		pthread_mutex_unlock(&(philo->info->mut_action));
		usleep(500);
	}
	return (NULL);
}

/* Continue the process until the philosopher is dead. */
void	*philosopher(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (check_philo_status(philo))
	{
		if (get_forks(philo) == false)
			break ;
		if (philo_eat(philo) == false)
			break ;
		if (put_forks(philo) == false)
			break ;
		if (philo_sleep(philo) == false)
			break ;
		if (philo_think(philo) == false)
			break ;
	}
	return (NULL);
}

bool	launch_thread(t_philos *philos, pthread_t *thread, void*(*func)(void*))
{
	int	i;

	i = 0;
	while (i < philos->info->philo_num)
	{
		pthread_create(&thread[i], NULL, func, philos);
		philos = philos->left;
		i += 1;
	}
	return (true);
}

void	join_all_thread(int philo_num, pthread_t **thread)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_join(thread[PHILO][i], NULL);
		pthread_join(thread[MONITOR][i], NULL);
		i += 1;
	}
}
