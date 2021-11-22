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
	if (philo->info->status == DIED)
	{
		return (false);
	}
	else if (philo->info->end_eat_flag == 1 && \
			philo->info->eat_num >= philo->info->end_eat_num_to_finish)
	{
		return (false);
	}
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
			philo->info->status = DIED;
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
		get_forks(philo);
		philo_eat(philo);
		put_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_detach(thread);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo_inf	info;
	t_philos	*philos;

	if (validate_args(argc - 1, argv) == false)
	{
		return (1);
	}
	init_info_struct(&info, argc - 1, argv);
	philos = create_philos_struct(info.philo_num);
	init_philos_struct(philos, &info);

	pthread_t	*thread;
	int	i;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * info.philo_num);
	i = 0;
	while (i < info.philo_num)
	{
		pthread_create(&thread[i], NULL, philosopher, philos);
		philos = philos->left;
		i += 1;
	}
	i = 0;
	while (i < info.philo_num)
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}

	t_philos	*tmp;
	i = 0;
	while (i < info.philo_num)
	{
		tmp = philos->left;
		free(philos->last_eat_time);
		free(philos);
		philos = tmp;
		i += 1;
	}
	free(thread);

	return (0);
}

__attribute__((destructor))
void    destructor(void)
{
    int    status;

    status = system("leaks philo &> leaksout");
    if (status)
    {
        write(2, "leak!!!\n", 8);
        system("cat leaksout >/dev/stderr");
        exit(1);
    }
}
