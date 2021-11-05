/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:20 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 17:04:32 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	is_digit(char *arg)
{
	int	decimal_flag;
	int	i;

	decimal_flag = 0;
	i = 0;
	while (arg[i] == '\0')
	{
		if (arg[i] == '.' && decimal_flag == 0)
		{
			decimal_flag = 1;
			i += 1;
		}
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			return (false);
		}
		i += 1;
	}
	return (true);
}

bool	validate_args(int num, char **args)
{
	int	i;

	if (num < 4 || num > 5)
	{
		return (false);
	}
	i = 1;
	while (i <= num)
	{
		if (is_digit(args[i]) == false)
		{
			return (false);
		}
		i += 1;
	}
	return (true);
}

void	init_info_struct(t_philo_inf *inf, int num, char **args)
{
	inf->philo_num = ft_atoi(args[1]);
	inf->time_to_die = ft_atoi(args[2]);
	inf->time_to_eat = ft_atoi(args[3]);
	inf->time_to_sleep = ft_atoi(args[4]);
	if (num == 5)
	{
		inf->end_eat_num_to_finish = ft_atoi(args[5]);
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

void	init_philos_struct(t_philos *philos, int num)
{
	long	timestamp;
	int		i;

	timestamp = get_timestamp();
	i = 1;
	while (i <= num)
	{
		philos->id = i;
		philos->status = LIVE;
		philos->last_eat_time = (long *)malloc(sizeof(long));
		*(philos->last_eat_time) = timestamp;
		pthread_mutex_init(&philos->mut_fork, NULL);
		pthread_mutex_init(&philos->mut_last_eat_time, NULL);
		philos = philos->left;
		i += 1;
	}
}
