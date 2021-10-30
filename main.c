#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

void	test_gettimeofday(void);
void	test_pthread_and_mutex(void);

int	main(int argc, char ** argv)
{
	/* compile command */
	//gcc main.c -g -fsanitize=address

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
