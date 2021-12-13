/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:24:43 by yootaki           #+#    #+#             */
/*   Updated: 2021/12/13 17:24:50 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	check_philo_status(t_philos *philo)
{
	if (philo->info->status == FINISH)
	{
		return (false);
	}
	return (true);
}

void	check_philo_life(t_philos *philo)
{
	long		now;
	long		last;

	now = get_timestamp();
	last = philo->last_eat_time;
	if (now - last >= philo->info->time_to_die)
	{
		philo->info->status = FINISH;
		printf("%s%ld %d died%s\n", RED, now, philo->id, RESET);
	}
}

void	check_philo_eatnum(t_philos *philo)
{
	int	eat_end_philo_num;
	int	i;

	if (philo->info->end_eat_flag == false)
	{
		return ;
	}
	eat_end_philo_num = 0;
	i = 0;
	while (i < philo->info->philo_num)
	{
		if (philo->eat_num >= philo->info->end_eat_num_to_finish)
		{
			eat_end_philo_num += 1;
		}
		philo = philo->left;
		i += 1;
	}
	if (eat_end_philo_num == philo->info->philo_num)
	{
		philo->info->status = FINISH;
	}
}
