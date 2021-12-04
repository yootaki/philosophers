/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:20 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/07 22:07:18by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_info_struct(t_philo_info *info, int argc, char **args)
{
	info->status = CONTINUE;
	info->philo_num = ft_atoi(args[1]);
	info->time_to_die = ft_atoi(args[2]);
	info->time_to_eat = ft_atoi(args[3]);
	info->time_to_sleep = ft_atoi(args[4]);
	pthread_mutex_init(&info->mut_action, NULL);
	if (argc == 5)
	{
		info->end_eat_flag = true;
		info->end_eat_num_to_finish = ft_atoi(args[5]);
	}
	else
	{
		info->end_eat_flag = false;
		info->end_eat_num_to_finish = 0;
	}
}

bool	create_philos_struct(int philo_num, t_philos **philos)
{
	t_philos	*top;
	t_philos	*new;
	t_philos	*tmp;

	*philos = (t_philos *)malloc(sizeof(t_philos));
	if (*philos == NULL)
		return (false);
	top = *philos;
	tmp = *philos;
	philo_num -= 1;
	while (philo_num > 0)
	{
		new = (t_philos *)malloc(sizeof(t_philos));
		if (new == NULL)
			return (false);
		tmp->left = new;
		new->right = tmp;
		tmp = new;
		philo_num -= 1;
	}
	tmp->left = top;
	top->right = tmp;
	*philos = top;
	return (true);
}

bool	create_threads(int philo_num, pthread_t **thread)
{
	thread[PHILO] = (pthread_t *)malloc(sizeof(pthread_t) * philo_num);
	thread[MONITOR] = (pthread_t *)malloc(sizeof(pthread_t) * philo_num);
	if (thread[PHILO] == NULL || thread[MONITOR] == NULL)
	{
		return (false);
	}
	return (true);
}

void	init_philos_struct(t_philos *philos, t_philo_info *info)
{
	long	timestamp;
	int		i;

	timestamp = get_timestamp();
	i = 1;
	while (i <= info->philo_num)
	{
		philos->info = info;
		philos->id = i;
		philos->eat_num = 0;
		philos->last_eat_time = timestamp;
		pthread_mutex_init(&philos->mut_fork, NULL);
		philos = philos->left;
		i += 1;
	}
}
