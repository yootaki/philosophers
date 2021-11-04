/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:20 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/03 23:18:03 by yootaki          ###   ########.fr       */
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

void	init_philos_struct(t_philos *philos, int num)
{
	struct timeval	tv;
	int	i;

	if (gettimeofday(&tv, NULL))
	{
		printf("get time error!\n");
	}
	i = 0;
	while (i < num)
	{
		philos[i].id = i + 1;
		philos[i].status = LIVE;
		philos[i].last_eat_time = tv;
		i += 1;
	}
}
