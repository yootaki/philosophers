/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:55:58 by yootaki           #+#    #+#             */
/*   Updated: 2021/12/05 08:56:19 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_all(int philo_num, t_philos *philos, pthread_t **thread)
{
	t_philos	*tmp;
	int			i;

	pthread_mutex_destroy(&(philos->info->mut_action));
	if (philos != NULL)
	{
		i = 0;
		while (i < philo_num)
		{
			tmp = philos->left;
			pthread_mutex_destroy(&(philos->mut_fork));
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
