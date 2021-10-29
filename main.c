#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

//gcc main.c -g -fsanitize=address

void	test_gettimeofday(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL)) {
		printf("%s\n", "error");
	}
	printf("tv1:%ld,%d\n", tv.tv_sec, tv.tv_usec);

	if (gettimeofday(&tv, NULL)) {
		printf("%s\n", "error");
	}
	printf("tv2:%ld,%d\n", tv.tv_sec, tv.tv_usec);
}

void	*ret_str(void *str)
{
		static int	n = 1;
		pthread_mutex_t	mut;

		pthread_mutex_init(&mut, NULL);
		pthread_mutex_lock(&mut);
		printf("thread created No.%d.\n", n++);
		pthread_mutex_unlock(&mut);
		usleep(1);
		return (NULL);
}

void	test_pthread_and_mutex(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	void		*retval;
	
	if (pthread_create(&thread1, NULL, ret_str, NULL) != 0)
			printf("create thread error\n");
	if (pthread_create(&thread2, NULL, ret_str, NULL) != 0)
			printf("create thread error\n");
	if (pthread_create(&thread3, NULL, ret_str, NULL) != 0)
			printf("create thread error\n");
	pthread_join(thread1, &retval);
	pthread_join(thread2, &retval);
	pthread_join(thread3, &retval);
	pthread_detach(thread1);
	pthread_detach(thread2);
	pthread_detach(thread3);
}

int	main(int argc, char ** argv)
{
	/* ToDo */
	//引数のチェック
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
