/* compile command */
//gcc main.c -g -fsanitize=address

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#include "philosopher.h"

//[./philo 3 600 300 400 2]
typedef struct s_philo_inf
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	end_num_to_finish;
}t_philo_inf;

void	test_gettimeofday(void);
void	test_pthread_and_mutex(void);

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
			return (false);
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
			return (false);
		i += 1;
	}
	return (true);
}

void	create_philosopher_info_struct(t_philo_inf *inf, char **args)
{
	//philo num
	inf->philo_num = ft_atoi(args[0]);
	//dead time
	inf->time_to_die = ft_atoi(args[1]);
	//eat time
	inf->time_to_eat = ft_atoi(args[2]);
	//sleep time
	inf->time_to_sleep = ft_atoi(args[3]);
	//[ end eating time ]
	inf->end_num_to_finish = ft_atoi(args[4]);
}

int	main(int argc, char **argv)
{
	t_philo_inf inf;

	/* ToDo */
	//引数のチェック
	if(validate_args(argc - 1, argv) == false)
		return (1);
	//それぞれのオプションを格納（構造体？）
	create_philosopher_info_struct(&inf, argv);
	//哲学者の人数分の構造体を作成＆初期化?
	//プログラム開始
	//スレッドの作成？
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
	
	/* Test */
	test_gettimeofday();
	test_pthread_and_mutex();

	return (0);
}
