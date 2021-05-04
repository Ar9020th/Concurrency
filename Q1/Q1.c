#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#define lp(i,a,b) for(int i=a;i<b;i++)
int * shareMem(size_t size) {
	key_t mem_key = IPC_PRIVATE;
	int shm_id = shmget(mem_key, size, IPC_CREAT | 0666);
	return (int*)shmat(shm_id, NULL, 0);
}
void selectionsort(int* arr, int l, int r)
{
	// printf("%d %d\n", l, r);
	int minidx;
	lp(i, l, r)
	{
		// printf("wdawqwwwwwwww\n");
		minidx = i;
		lp(j, i + 1, r + 1)
		{
			if (arr[j] < arr[minidx])
				minidx = j;
		}
		int temp = arr[minidx];
		arr[minidx] = arr[i];
		arr[i] = temp;
	}
	// printf("wdawqwwwwwwww\n");
	// printf("%d %d\n", l, r);
	// lp(k, l, r + 1)
	// {
	// 	printf("%d\n", arr[k]);
	// }
}
void merge(int* arr, int l, int m, int r)
{
	int na1, na2;
	na1 = m - l + 1;
	na2 = r - m;
	int a1[na1], a2[na2];
	lp(i, 0, na1)
	{
		a1[i] = arr[l + i];
	}
	lp(i, 0, na2)
	{
		a2[i] = arr[m + 1 + i];
	}
	int p1 = 0, p2 = 0, p3 = l;
	while (p1 < na1 && p2 < na2)
	{
		if (a1[p1] <= a2[p2])
			arr[p3++] = a1[p1++];
		else
			arr[p3++] = a2[p2++];
	}
	while (p1 < na1)
	{
		arr[p3++] = a1[p1++];
	}
	while (p2 < na2)
	{
		arr[p3++] = a2[p2++];
	}
	// lp(i, l, r)
	// {
	// 	printf("%d", arr[i]);
	// }
}
void mergesort(int* arr, int l, int r, int method)
{
	if (method == 0)
	{
		if (l < r)
		{
			int mid = (r + l) / 2;
			pid_t lpid, rpid;
			if ((r - l + 1) <= 5)
			{
				selectionsort(arr, l, r);
				return;
			}
			lpid = fork();
			if (lpid < 0)
			{
				perror("There was some issue in creating left process\n");
				exit(1);
			}
			if (lpid == 0)
			{
				mergesort(arr, l, mid , 0);
				_exit(0);
			}
			else
			{
				rpid = fork();
				if (rpid < 0)
				{
					perror("There was some issue in creating left process\n");
					exit(1);
				}
				if (rpid == 0)
				{
					mergesort(arr, mid + 1, r, 0);
					_exit(0);
				}
				else
				{
					int status;
					waitpid(lpid, &status, 0);
					waitpid(rpid, &status, 0);
				}
			}
			merge(arr, l, mid, r);
		}
	}
	else if (method == 1)
	{
		if (l < r)
		{
			int m = l + (r - l) / 2;
			mergesort(arr, l, m, 1);
			mergesort(arr, m + 1, r, 1);
			merge(arr, l, m, r);
		}
	}
}
int main()
{
	int n;
	double t1, t2;
	struct timespec tm;
	scanf("%d", &n);
	int* arr = shareMem(sizeof(int) * n);
	int arr2[n];
	lp(i, 0, n)
	{
		scanf("%d", &arr[i]);
		arr2[i] = arr[i];
	}
	// tm = clock();
	clock_gettime(CLOCK_MONOTONIC_RAW, &tm);
	t1 = tm.tv_nsec / (1e9) + tm.tv_sec;
	mergesort(arr, 0, n - 1, 0);
	// tm = clock() - tm;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tm);
	t2 = tm.tv_nsec / (1e9) + tm.tv_sec;
	printf("Sorted Array Is:-\n");
	lp(i, 0, n)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("\033[0;36m");
	// t1 = (1.0 * tm) / CLOCKS_PER_SEC;
	printf("Time Taken by Recursive Splitting is %0.8lf seconds\n", t2 - t1);
	printf("\033[0m");
	// tm = clock();
	clock_gettime(CLOCK_MONOTONIC_RAW, &tm);
	t1 = tm.tv_nsec / (1e9) + tm.tv_sec;
	mergesort(arr2, 0, n - 1, 1);
	clock_gettime(CLOCK_MONOTONIC_RAW, &tm);
	t2 = tm.tv_nsec / (1e9) + tm.tv_sec;
	// tm = clock() - tm;
	printf("Sorted Array Is:-\n");
	lp(i, 0, n)
	{
		printf("%d ", arr2[i]);
	}
	printf("\n");
	printf("\033[0;36m");
	// t2 = (1.0 * tm) / CLOCKS_PER_SEC;
	printf("Time Taken by Normal Merge Sort is %0.8lf seconds\n", t2 - t1);
	printf("\033[0m");
}