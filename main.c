#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

/* compile command */
//gcc main.c -g -fsanitize=address

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

	if (num < 4 && num > 5)
			return (false);
	i = 1;
	while (i <= num)
	{
		if (is_digit(args[i]) == false)
				return (false);
		i += 1;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	/* ToDo */
	//引数のチェック
	if(validate_args(argc - 1, argv) == false)
			return (1);
	//それぞれのオプションを格納（構造体？）
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
