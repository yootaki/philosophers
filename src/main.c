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

int	main(int argc, char **argv)
{
	t_philo_info	info;
	t_philos		*philos;
	pthread_t		*thread[NUM];

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
