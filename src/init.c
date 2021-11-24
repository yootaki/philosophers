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

void	init_info_struct(t_philo_inf *info, int num, char **args)
{
	info->status = CONTINUE;
	info->philo_num = ft_atoi(args[1]);
	info->time_to_die = ft_atoi(args[2]);
	info->time_to_eat = ft_atoi(args[3]);
	info->time_to_sleep = ft_atoi(args[4]);
	info->eat_num = 0;
	if (num == 5)
	{
		info->end_eat_flag = 1;
		info->end_eat_num_to_finish = ft_atoi(args[5]);
	}
	else
	{
		info->end_eat_flag = 0;
	}
}

t_philos	*create_philos_struct(int num)
{
	t_philos	*philos;
	t_philos	*top;
	t_philos	*new;

	philos = (t_philos *)malloc(sizeof(t_philos));
	top = philos;
	num -= 1;
	while (num > 0)
	{
		new = (t_philos *)malloc(sizeof(t_philos));
		philos->left = new;
		new->right = philos;
		philos = new;
		num -= 1;
	}
	philos->left = top;
	top->right = philos;
	return (top);
}

void	init_philos_struct(t_philos *philos, t_philo_inf *info)
{
	long	timestamp;
	int		i;

	timestamp = get_timestamp();
	i = 1;
	while (i <= info->philo_num)
	{
		philos->info = info;
		philos->id = i;
		philos->last_eat_time = (long *)malloc(sizeof(long));
		*(philos->last_eat_time) = timestamp;
		pthread_mutex_init(&philos->mut_fork, NULL);
		pthread_mutex_init(&philos->info->mut_action, NULL);
		philos = philos->left;
		i += 1;
	}
}
