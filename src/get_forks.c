/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:36:46 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/30 14:50:13ootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	get_right_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->mut_fork);
	pthread_mutex_lock(&philo->info->mut_action);
	if (check_philo_status(philo) == false)
	{
		pthread_mutex_unlock(&philo->info->mut_action);
		pthread_mutex_unlock(&(philo->mut_fork));
		return (false);
	}
	print_philo_action(get_timestamp(), philo->id, GET_FORK);
	pthread_mutex_unlock(&philo->info->mut_action);
	return (true);
}

bool	get_left_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->left->mut_fork);
	pthread_mutex_lock(&philo->info->mut_action);
	if (check_philo_status(philo) == false)
	{
		pthread_mutex_unlock(&philo->info->mut_action);
		pthread_mutex_unlock(&(philo->left->mut_fork));
		return (false);
	}
	print_philo_action(get_timestamp(), philo->id, GET_FORK);
	pthread_mutex_unlock(&philo->info->mut_action);
	return (true);
}

bool	get_forks(t_philos *philo)
{
	if (philo->id % 2 == 1)
	{
		usleep(500);
		if (get_right_fork(philo) == false)
			return (false);
		if (philo->info->philo_num == 1)
			return (false);
		if (get_left_fork(philo) == false)
		{
			pthread_mutex_unlock(&(philo->mut_fork));
			return (false);
		}
	}
	else
	{
		if (get_left_fork(philo) == false)
			return (false);
		if (get_right_fork(philo) == false)
		{
			pthread_mutex_unlock(&(philo->left->mut_fork));
			return (false);
		}
	}
	return (true);
}
