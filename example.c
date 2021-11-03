#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define M 50

sem_t forks[N];

typedef struct
{
	int	index;
}parg;

int	first(int p)
{
	if (p == 4)
	{
		return ((p + 1) / N);
	}
	return (p);
}

int	second(int p)
{
	if (p == 4)
	{
		return (p);
	}
	return ((p + 1) % N);
}

void	get_first_fork(int p)
{
	printf("philosopher %d get fork %d", p, first(p));
	sem_wait(&forks[first(p)]);
	printf(" ... Done\n");
}

void	get_second_fork(int p)
{
	printf("philosopher %d get fork %d", p, second(p));
	sem_wait(&forks[second(p)]);
	printf(" ... Done\n");
}

void	get_forks(int p)
{
	get_first_fork(p);
	usleep(((rand() % 5) + 1) * 1000);
	get_second_fork(p);
}

void	put_first_fork(int p)
{
	printf("philosopher %d put fork %d", p, first(p));
	sem_post(&forks[first(p)]);
	printf(" ... Done\n");
}

void	put_second_fork(int p)
{
	printf("philosopher %d put fork %d", p, second(p));
	sem_post(&forks[second(p)]);
	printf(" ... Done\n");
}

void	put_forks(int p)
{
	put_first_fork(p);
	put_second_fork(p);
}

void	think()
{
	usleep(((rand() % 5) + 1) * 1000);
}

void	eat()
{
	usleep(((rand() % 5) + 1) * 1000);
}

void	*philosopher(void *arg)
{
	parg *a;
	int	i;

	a = (parg *)arg;
	i = 0;
	while (i < M)
	{
		think();
		get_forks(a->index);
		eat();
		put_forks(a->index);
		i += 1;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int	i;

	//フォークを初期化
	i = 0;
	while (i < N)
	{
		sem_init(&forks[i], 0, 1);
		i += 1;
	}

	//初期化とphilosopherのスタート
	pthread_t p[N];
	parg a[N];
	i = 0;
	while (i < N)
	{
		a[i].index = i;
		pthread_create(&p[i], NULL, philosopher, &a[i]);
		i += 1;
	}

	i = 0;
	while (i < N)
	{
		pthread_join(p[i], NULL);
		i +=1;
	}

	printf("finished\n");
	return (0);
}
