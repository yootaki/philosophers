/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:40:35 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/07 22:41:07 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	put_first_fork(t_philos *philo)
{
	pthread_mutex_unlock(&philo->mut_fork);
}

void	put_second_fork(t_philos *philo)
{
	pthread_mutex_unlock(&philo->left->mut_fork);
}

void	put_forks(t_philos *philo)
{
	put_first_fork(philo);
	put_second_fork(philo);
}
