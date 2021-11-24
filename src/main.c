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

/* Monitor the philosopher's status and flag any deaths. */
void	*monitor(void *arg)
{
	t_philos	*philo;
	long		now;
	long		last;

	philo = (t_philos *)arg;
	while (check_philo_status(philo))
	{
		now = get_timestamp();
		pthread_mutex_lock(&(philo->info->mut_action));
		last = *(philo->last_eat_time);
		if (now - last >= philo->info->time_to_die)
		{
			philo->info->status = FINISH;
			printf("%s%ld %d died%s\n", RED, now, philo->id, RESET);
		}
		pthread_mutex_unlock(&(philo->info->mut_action));
		usleep(100);
	}
	return (NULL);
}

/* Continue the process until the philosopher is dead. */
void	*philosopher(void *arg)
{
	t_philos	*philo;
	pthread_t	thread;

	philo = (t_philos *)arg;
	pthread_create(&thread, NULL, monitor, philo);
	while (check_philo_status(philo))
	{
		if (get_forks(philo) == false)
			break ;
		if (philo_eat(philo) == false)
			break ;
		if (put_forks(philo) == false)
			break ;
		if (philo_sleep(philo) == false)
			break ;
		if (philo_think(philo) == false)
			break ;
	}
	pthread_detach(thread);
	return (NULL);
}

bool	launch_thread(int philo_num, t_philos *philos, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_create(&thread[i], NULL, philosopher, philos);
		philos = philos->left;
		i += 1;
	}
	return (true);
}

void	join_philo_thread(int philo_num, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}
}

void	free_all(int philo_num, t_philos *philos, pthread_t *thread)
{
	t_philos	*tmp;
	int			i;

	i = 0;
	while (i < philo_num)
	{
		tmp = philos->left;
		free(philos->last_eat_time);
		free(philos);
		philos = tmp;
		i += 1;
	}
	free(thread);
}

int	main(int argc, char **argv)
{
	t_philo_inf	info;
	t_philos	*philos;
	pthread_t	*thread;

	philos = NULL;
	thread = NULL;
	if (validate_args(argc - 1, argv) == false)
	{
		return (EXIT_FAILURE);
	}
	init_info_struct(&info, argc - 1, argv);
	philos = create_philos_struct(info.philo_num);
	if (philos == NULL)
		return (EXIT_FAILURE);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * info.philo_num);
	if (thread == NULL)
		return (EXIT_FAILURE);
	if (init_philos_struct(philos, &info) == false)
	{
		free_all(info.philo_num, philos, thread);
		return (EXIT_FAILURE);
	}
	if (launch_thread(info.philo_num, philos, thread) == false)
	{
		free_all(info.philo_num, philos, thread);
		return (EXIT_FAILURE);
	}
	join_philo_thread(info.philo_num, thread);
	free_all(info.philo_num, philos, thread);
	return (EXIT_SUCCESS);
}
