/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 23:32:55 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/30 14:26:28 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_philo_action(long timestamp, int id, char *action)
{
	printf("%ld %d %s\n", timestamp, id, action);
}

/* Function to sleep until a after_time. */
void	few_seconds_sleep(long after_time)
{
	long	now;

	while (1)
	{
		now = get_timestamp();
		if (now >= after_time)
		{
			break ;
		}
		usleep(500);
	}
}

/* Update the last time you ate and wait for an arbitrary number of seconds. */
bool	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&(philo->info->mut_action));
	if (philo->info->status == FINISH)
	{
		pthread_mutex_unlock(&(philo->mut_fork));
		pthread_mutex_unlock(&(philo->left->mut_fork));
		pthread_mutex_unlock(&(philo->info->mut_action));
		return (false);
	}
	philo->info->eat_num += 1;
	philo->last_eat_time = get_timestamp();
	print_philo_action(philo->last_eat_time, philo->id, EAT);
	pthread_mutex_unlock(&(philo->info->mut_action));
	few_seconds_sleep(philo->last_eat_time + philo->info->time_to_eat);
	return (true);
}

/* Wait for an arbitrary number of seconds. */
bool	philo_sleep(t_philos *philo)
{
	long	time;

	pthread_mutex_lock(&(philo->info->mut_action));
	time = get_timestamp();
	if (philo->info->status == FINISH)
	{
		pthread_mutex_unlock(&(philo->info->mut_action));
		return (false);
	}
	print_philo_action(time, philo->id, SLEEP);
	pthread_mutex_unlock(&(philo->info->mut_action));
	few_seconds_sleep(time + philo->info->time_to_sleep);
	return (true);
}

bool	philo_think(t_philos *philo)
{
	pthread_mutex_lock(&(philo->info->mut_action));
	if (philo->info->status == FINISH)
	{
		pthread_mutex_unlock(&(philo->info->mut_action));
		return (false);
	}
	print_philo_action(get_timestamp(), philo->id, THINK);
	pthread_mutex_unlock(&(philo->info->mut_action));
	return (true);
}
