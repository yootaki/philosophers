/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:40:35 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/24 11:23:14 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	put_first_fork(t_philos *philo)
{
	pthread_mutex_unlock(&philo->mut_fork);
	return (true);
}

bool	put_second_fork(t_philos *philo)
{
	pthread_mutex_unlock(&philo->left->mut_fork);
	return (true);
}

bool	put_forks(t_philos *philo)
{
	if (put_first_fork(philo) == false)
		return (false);
	if (put_second_fork(philo) == false)
		return (false);
	return (true);
}
