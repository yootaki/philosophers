/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:16:33 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 23:13:37y yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	check_philo_status(t_philos *philo)
{
	pthread_mutex_lock(&(philo->info->mut_action));
	if (philo->info->status == FINISH)
	{
		pthread_mutex_unlock(&(philo->info->mut_action));
		return (false);
	}
	else if (philo->info->end_eat_flag == 1 && \
			philo->info->eat_num >= philo->info->end_eat_num_to_finish)
	{
		pthread_mutex_unlock(&(philo->info->mut_action));
		return (false);
	}
	pthread_mutex_unlock(&(philo->info->mut_action));
	return (true);
}

void	free_philos(int philo_num, t_philos *philos)
{
	t_philos	*tmp;
	int			i;

	i = 0;
	while (i < philo_num)
	{
		tmp = philos->left;
		free(philos);
		philos = tmp;
		i += 1;
	}
}

int	main(int argc, char **argv)
{
	t_philo_inf	info;
	t_philos	*philos;

	if (validate_args(argc - 1, argv) == false)
	{
		return (EXIT_FAILURE);
	}
	init_info_struct(&info, argc - 1, argv);
	philos = create_philos_struct(info.philo_num);
	if (philos == NULL)
		return (EXIT_FAILURE);
	init_philos_struct(philos, &info);
	if (launch_thread(philos, &philosopher) == false || \
		launch_thread(philos, &monitor) == false)
	{
		free_philos(info.philo_num, philos);
		return (EXIT_FAILURE);
	}
	free_philos(info.philo_num, philos);
	return (EXIT_SUCCESS);
}
