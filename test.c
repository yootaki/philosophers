#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

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


