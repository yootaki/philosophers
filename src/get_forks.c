/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:36:46 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/22 15:03:25 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	get_first_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->mut_fork);
	if (philo->info->status == DIED)
	{
		pthread_mutex_unlock(&(philo->mut_fork));
		return ;
	}
	print_philo_action(get_timestamp(), philo->id, GET_FORK);
}

void	get_second_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->left->mut_fork);
	if (philo->info->status == DIED)
	{
		pthread_mutex_unlock(&(philo->left->mut_fork));
		return ;
	}
	print_philo_action(get_timestamp(), philo->id, GET_FORK);
}

void	get_forks(t_philos *philo)
{
	if (philo->id % 2 == 1)
	{
		usleep(100);
		get_first_fork(philo);
		get_second_fork(philo);
	}
	else
	{
		get_second_fork(philo);
		get_first_fork(philo);
	}
}
