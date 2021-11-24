/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:36:46 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/24 11:20:02 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	get_first_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->mut_fork);
	pthread_mutex_lock(&philo->info->mut_action);
	if (philo->info->status == FINISH)
	{
		pthread_mutex_unlock(&philo->info->mut_action);
		pthread_mutex_unlock(&(philo->mut_fork));
		return (false);
	}
	pthread_mutex_unlock(&philo->info->mut_action);
	print_philo_action(get_timestamp(), philo->id, GET_FORK);
	return (true);
}

bool	get_second_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->left->mut_fork);
	pthread_mutex_lock(&philo->info->mut_action);
	if (philo->info->status == FINISH)
	{
		pthread_mutex_unlock(&philo->info->mut_action);
		pthread_mutex_unlock(&(philo->left->mut_fork));
		return (false);
	}
	pthread_mutex_unlock(&philo->info->mut_action);
	print_philo_action(get_timestamp(), philo->id, GET_FORK);
	return (true);
}

bool	get_forks(t_philos *philo)
{
	if (philo->id % 2 == 1)
	{
		usleep(100);
		if (get_first_fork(philo) == false)
			return (false);
		if (get_second_fork(philo) == false)
			return (false);
	}
	else
	{
		if (get_second_fork(philo) == false)
			return (false);
		if (get_first_fork(philo) == false)
			return (false);
	}
	return (true);
}
