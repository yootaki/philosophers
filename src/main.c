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

void	free_all(int philo_num, t_philos *philos, pthread_t **thread)
{
	t_philos	*tmp;
	int			i;

	if (philos != NULL)
	{
		i = 0;
		while (i < philo_num)
		{
			tmp = philos->left;
			free(philos);
			philos = tmp;
			i += 1;
		}
	}
	if (thread != NULL)
	{
		free(thread[PHILO]);
		free(thread[MONITOR]);
	}
}

int	main(int argc, char **argv)
{
	t_philo_inf	info;
	t_philos	*philos;
	pthread_t	*thread[NUM];

	if (validate_args(argc - 1, argv) == false)
		return (EXIT_FAILURE);
	init_info_struct(&info, argc - 1, argv);
	if (create_philos_struct(info.philo_num, &philos) == false || \
		create_threads(info.philo_num, thread) == false)
	{
		free_all(info.philo_num, philos, NULL);
		return (EXIT_FAILURE);
	}
	init_philos_struct(philos, &info);
	if (launch_thread(philos, thread[PHILO], &philosopher) == false || \
		launch_thread(philos, thread[MONITOR], &monitor) == false)
	{
		free_all(info.philo_num, philos, thread);
		return (EXIT_FAILURE);
	}
	join_all_thread(info.philo_num, thread);
	free_all(info.philo_num, philos, thread);
	return (EXIT_SUCCESS);
}
