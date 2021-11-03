/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:48:42 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/02 16:30:39by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compile command */
//gcc main.c -g -fsanitize=address

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#include "philosopher.h"

int	*forks;
int	n;

enum status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

//[$ ./philo 3 600 300 400 2]
typedef struct s_philo_inf
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	end_eat_num_to_finish;
}t_philo_inf;

typedef struct s_philos
{
	struct s_philos	*left;
	struct s_philos	*right;
	int				id;
	enum status		status;
}t_philos;

// ---------- init or validate ----------
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
	t_philos	*top;
	t_philos	*tmp;
	t_philos	*new;

	top = (t_philos *)malloc(sizeof(t_philos));
	tmp = top;
	while (num > 0)
	{
		new = (t_philos *)malloc(sizeof(t_philos));//malloc
		tmp->left = new;
		new->right = tmp;
		tmp = tmp->left;
		num -= 1;
	}
	tmp->left = top;
	top->right = tmp;
	return (top);
}

void	init_philos_struct(t_philos *philos, int num)
{
	int	i;

	i = 1;
	while (i <= num)
	{
		philos->id = i;
		philos->status = THINKING;
		philos = philos->left;
		i += 1;
	}
}
// --------------------------------------

// ---------- debug ----------
void	print_philos(t_philos *philos, int num)
{
	while (num > 0)
	{
		printf("id=%d,status=%d\n", philos->id, philos->status);
		philos = philos->left;
		num -= 1;
	}
}
// ---------------------------

int	first(int id)
{
	return (id);
}

int	second(int id)
{
	return ((id + 1) % n);
}

void	get_first_fork(int id)
{
	pthread_mutex_t	mut;

	pthread_mutex_init(&mut, NULL);
	pthread_mutex_lock(&mut);
	printf("philosopher %d : get fork %d", id, first(id));
	forks[first(id)] = 1;
	pthread_mutex_unlock(&mut);
	printf(" ... Done\n");
}

void	get_second_fork(int id)
{
	pthread_mutex_t	mut;

	pthread_mutex_init(&mut, NULL);
	pthread_mutex_lock(&mut);
	printf("philosopher %d : get fork %d", id, second(id));
	forks[second(id)] = 1;
	pthread_mutex_unlock(&mut);
	printf(" ... Done\n");
}

void	get_forks(int id)
{
	get_first_fork(id);
	usleep(((rand() % 5) + 1) * 1000);
	get_second_fork(id);
}

void	put_first_fork(int id)
{
	pthread_mutex_t	mut;

	pthread_mutex_init(&mut, NULL);
	pthread_mutex_lock(&mut);
	printf("philosopher %d : put fork %d", id, first(id));
	forks[first(id)] = 0;
	pthread_mutex_unlock(&mut);
	printf(" ... Done\n");
}

void	put_second_fork(int id)
{
	pthread_mutex_t	mut;

	pthread_mutex_init(&mut, NULL);
	pthread_mutex_lock(&mut);
	printf("philosopher %d : put fork %d", id, second(id));
	forks[second(id)] = 0;
	pthread_mutex_unlock(&mut);
	printf(" ... Done\n");
}

void	put_forks(int id)
{
	put_first_fork(id);
	put_second_fork(id);
}

void	think(int id)
{
	printf("philosopher %d : thinking\n", id);
	usleep(((rand() % 5) + 1) * 1000);
}

void	eat(int id)
{
	printf("philosopher %d : eating\n", id);
	usleep(((rand() % 5) + 1) * 1000);
}

void	philo_sleep(int id)
{
	printf("philosopher %d : sleeping\n", id);
	usleep(((rand() % 5) + 1) * 1000);
}

void	*philosopher(void *arg)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)arg;
	i = 0;
	while (i < 10)
	{
		think(philo->id);
		get_forks(philo->id);
		eat(philo->id);
		put_forks(philo->id);
		philo_sleep(philo->id);
		i += 1;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo_inf	inf;
	t_philos	*philos;

	if(validate_args(argc - 1, argv) == false)
	{
		return (1);
	}
	init_info_struct(&inf, argc - 1, argv);
	philos = create_philos_struct(inf.philo_num - 1);
	init_philos_struct(philos, inf.philo_num);

	// print_philos(philos, inf.philo_num);//debug

	//4. プログラム開始
	//->スレッドの作成？
	//
	//=== 今回はモニタを使った解法でやってみる(一旦) ===
	// フォークを持てるかの確認
	// --持てたら持ってmutex_lock
	// ----もし2本持っていたら食事
	// ----その間も死亡までの時間を各哲学者について確認を取る
	// ------時間が立ったらmutex_unlock
	// --------食事が終わったらフォークをおいて寝る
	// --------寝終わったらフォークが空くまで思考
	// --------他の哲学者は食事ができるかを確認
	// --------
	//
	//死亡までの時間を監視しておいて超えたら死亡の処理
	forks = (int *)malloc(sizeof(int) * inf.philo_num);
	n = inf.philo_num;
	pthread_t	*thread;
	int	i;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * inf.philo_num);
	i = 0;
	while (i < inf.philo_num)
	{
		pthread_create(&thread[i], NULL, philosopher, philos);
		philos = philos->left;
		i += 1;
	}

	//5. threadの終了？結合？
	i = 0;
	while (i < inf.philo_num)
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}

	//6. philos構造体とthreadの解放（free）
	free(forks);
	free(thread);

	printf("Finished!!!\n");
	return (0);
}
