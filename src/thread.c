/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:10:17 by yootaki           #+#    #+#             */
/*   Updated: 2021/12/05 08:18:52by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/* Monitor the philosopher's status and flag any deaths. */
void	*monitor(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->info->mut_action));
		if (check_philo_status(philo) == false)
		{
			pthread_mutex_unlock(&(philo->info->mut_action));
			break ;
		}
		check_philo_life(philo);
		check_philo_eatnum(philo);
		pthread_mutex_unlock(&(philo->info->mut_action));
		usleep(2500);
	}
	return (NULL);
}

/* Continue the process until the philosopher is dead. */
void	*philosopher(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
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
