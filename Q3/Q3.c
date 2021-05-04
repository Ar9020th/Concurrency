#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define lp(i,a,b) for(int i=a;i<b;i++)
#define rlp(i,a,b) for(int i=b;i>=a;i--)
typedef struct performer {
	char name[10];
	char ic;
	int arrivaltime;
} performer;
struct acou
{
	char prev;
	char name[10];
	sem_t mutex;
} acous[1000];
struct ele
{
	char prev;
	char name[10];
	sem_t mutex;
} elec[1000];
struct coordinator
{
	int available;
	pthread_mutex_t lock;
} coordinators[1000];
int k, a, e, c, t1, t2;
double t;
performer performers[1000];
pthread_t per[1000];
pthread_t atics[1000];
int min(int a, int b)
{
	return a > b ? b : a;
}
int genrandom(int lower, int upper)
{
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}
int checkelec(char* name, char ch, int time)
{
	int idx = -1;
	lp(i, 0, e)
	{
		// sem_wait(&elec[i].mutex);
		if (elec[i].prev == '0')
		{
			sem_wait(&elec[i].mutex);
			elec[i].prev = ch;
			strcpy(elec[i].name, name);
			idx = i;
			break;
		}
	}
	return idx;
}
int checkacous(char* name, char ch, int time)
{
	int idx = -1;
	lp(i, 0, a)
	{
		if (acous[i].prev == '0')
		{
			sem_wait(&acous[i].mutex);
			acous[i].prev = ch;
			strcpy(acous[i].name, name);
			idx = i;
			break;
		}
	}
	return idx;
}
void collectTshirt(char* name)
{
	int terminate = 1;
	while (terminate)
	{
		lp(i, 0, c)
		{
			if (coordinators[i].available == 1)
			{
				pthread_mutex_lock(&coordinators[i].lock);
				printf("%s collecting T-shirt\n", name);
				fflush(stdout);
				coordinators[i].available = 0;
				sleep(2);
				coordinators[i].available = 1;
				terminate = 0;
				printf("T-shirt collected\n");
				fflush(stdout);
				pthread_mutex_unlock(&coordinators[i].lock);
				break;
			}
		}
	}
}
void* allot(void* x)
{
	performer* inp = (performer*) x;
	// printf("tmkc%s\n", inp->name);
	sleep(inp->arrivaltime);
	printf("%s %c Arrived\n", inp->name, inp->ic);
	fflush(stdout);
	srand(time(0));
	int time1 = genrandom(t1, t2);
	time_t begin;
	time_t now;
	volatile double elapsed;
	time(&begin);
	int terminate = 1;
	int flag = 0;
	while (terminate)
	{
		if (inp->ic == 'p' || inp->ic == 'g')
		{
			// printf("asc\n");
			fflush(stdout);
			int x = genrandom(1, 2);
			if (x == 1)
			{
				// printf("lnrfger\n");
				fflush(stdout);
				int idx;
				idx = checkacous(inp->name, inp->ic, time1);
				if (idx == -1)
				{
					idx = checkelec(inp->name, inp->ic, time1);
					if (idx != -1)
					{
						printf("%s performing %c at electric stage for %d sec\n", inp->name, inp->ic, time1);
						fflush(stdout);
						flag = 1;
						sleep(time1);
						if (elec[idx].prev == 's')
							sleep(2);
						elec[idx].prev = '0';
						// elec[idx].prevtime = 0;
						printf("%s performance at electric stage finished\n", inp->name);
						fflush(stdout);
						sem_post(&elec[idx].mutex);
						collectTshirt(inp->name);
						pthread_exit(NULL);
						break;
					}
				}
				else
				{
					printf("%s performing %c at acoustic stage for %d sec\n", inp->name, inp->ic, time1);
					fflush(stdout);
					flag = 1;
					sleep(time1);
					if (acous[idx].prev == 's')
						sleep(2);
					acous[idx].prev = '0';
					// acous[idx].prevtime = 0;
					printf("%s performance at acoustic stage finished\n", inp->name);
					fflush(stdout);
					sem_post(&acous[idx].mutex);
					collectTshirt(inp->name);
					pthread_exit(NULL);
					break;
				}
			}
			else
			{
				// printf("bfbewfef\n");
				// fflush(stdout);
				int idx;
				idx = checkelec(inp->name, inp->ic, time1);
				if (idx == -1)
				{
					idx = checkacous(inp->name, inp->ic, time1);
					if (idx != -1)
					{
						printf("%s performing %c at acoustic stage for %d sec\n", inp->name, inp->ic, time1);
						fflush(stdout);
						flag = 1;
						sleep(time1);
						if (acous[idx].prev == 's')
							sleep(2);
						acous[idx].prev = '0';
						// acous[idx].prevtime = 0;
						printf("%s performance at acoustic stage finished\n", inp->name);
						fflush(stdout);
						sem_post(&acous[idx].mutex);
						collectTshirt(inp->name);
						pthread_exit(NULL);
						break;
					}
				}
				else
				{
					printf("%s performing %c at electric stage for %d sec\n", inp->name, inp->ic, time1);
					fflush(stdout);
					flag = 1;
					sleep(time1);
					if (elec[idx].prev == 's')
						sleep(2);
					elec[idx].prev = '0';
					// elec[idx].prevtime = 0;
					printf("%s performance at electric stage finished\n", inp->name);
					fflush(stdout);
					sem_post(&elec[idx].mutex);
					collectTshirt(inp->name);
					pthread_exit(NULL);
					break;
				}
			}
		}
		if (inp->ic == 'v')
		{
			int idx = checkacous(inp->name, inp->ic, time1);
			if (idx != -1)
			{
				printf("%s performing %c at acoustic stage for %d sec\n", inp->name, inp->ic, time1);
				fflush(stdout);
				flag = 1;
				sleep(time1);
				if (acous[idx].prev == 's')
					sleep(2);
				acous[idx].prev = '0';
				// acous[idx].prevtime = 0;
				printf("%s performance at acoustic stage finished\n", inp->name);
				fflush(stdout);
				sem_post(&acous[idx].mutex);
				collectTshirt(inp->name);
				pthread_exit(NULL);
				break;
			}
		}
		if (inp->ic == 'b')
		{
			int idx = checkelec(inp->name, inp->ic, time1);
			if (idx != -1)
			{
				printf("%s performing %c at electric stage for %d sec\n", inp->name, inp->ic, time1);
				fflush(stdout);
				flag = 1;
				sleep(time1);
				if (elec[idx].prev == 's')
					sleep(2);
				elec[idx].prev = '0';
				// elec[idx].prevtime = 0;
				printf("%s performance at electric stage finished\n", inp->name);
				fflush(stdout);
				sem_post(&elec[idx].mutex);
				collectTshirt(inp->name);
				pthread_exit(NULL);
				break;
			}
		}
		if (inp->ic == 's')
		{
			int chose1 = genrandom(1, 2);
			if (a == 0)
				chose1 = 2;
			if (e == 0)
				chose1 = 1;
			if (chose1 == 1)
			{
				int chose2 = genrandom(1, 2);
				if (chose2 == 1)
				{
					int idx;
					idx = checkacous(inp->name, inp->ic, time1);
					if (idx == -1)
					{
						lp(i, 0, a)
						{
							if (acous[i].prev != 's')
							{
								sem_wait(&acous[i].mutex);
								acous[i].prev = 's';
								idx = i;
								printf("%s joined %s's performance, performance extended by 2 secs\n", inp->name, acous[i].name);
								fflush(stdout);
								flag = 1;
								while (acous[i].prev != '0')
								{}
								sem_post(&acous[i].mutex);
								pthread_exit(NULL);
								break;
							}
							else
								sem_post(&acous[i].mutex);
						}
						// continue;
					}
					else
					{
						printf("%s performing %c at acoustic stage for %d sec\n", inp->name, inp->ic, time1);
						fflush(stdout);
						flag = 1;
						sleep(time1);
						acous[idx].prev = '0';
						printf("%s performance at acoustic stage finished\n", inp->name);
						fflush(stdout);
						sem_post(&acous[idx].mutex);
						pthread_exit(NULL);
						break;
					}
				}
				else
				{
					int idx = -1;
					lp(i, 0, a)
					{
						if (acous[i].prev != 's' && acous[i].prev != '0')
						{
							sem_wait(&acous[i].mutex);
							acous[i].prev = 's';
							idx = i;
							printf("%s joined %s's performance, performance extended by 2 secs\n", inp->name, acous[i].name);
							fflush(stdout);
							flag = 1;
							// sleep(time1);
							while (acous[i].prev != '0')
							{}
							sem_post(&acous[i].mutex);
							pthread_exit(NULL);
							break;
						}
						else
							sem_post(&acous[idx].mutex);
					}
					if (idx == -1)
					{
						idx = checkacous(inp->name, inp->ic, time1);
						if (idx != -1)
						{
							// sem_wait(&acous[i].mutex);
							printf("%s performing %c at acoustic stage for %d sec\n", inp->name, inp->ic, time1);
							fflush(stdout);
							flag = 1;
							sleep(time1);
							acous[idx].prev = '0';
							printf("%s performance at acoustic stage finished\n", inp->name);
							fflush(stdout);
							sem_post(&acous[idx].mutex);
							pthread_exit(NULL);
							break;
						}
						// else
						// continue;
					}
				}
			}
			else
			{
				int chose2 = genrandom(1, 2);
				if (chose2 == 1)
				{
					int idx;
					idx = checkelec(inp->name, inp->ic, time1);
					if (idx == -1)
					{
						lp(i, 0, e)
						{
							if (elec[i].prev != 's')
							{
								sem_wait(&elec[i].mutex);
								// if (elec[i].prevtime > (time1 + 2))
								// {
								// 	elec[i].prev = 's';
								// }
								elec[i].prev = 's';
								idx = i;
								printf("%s joined %s's performance, performance extended by 2 secs\n", inp->name, elec[i].name);
								fflush(stdout);
								flag = 1;
								// sleep(time1);
								while (elec[i].prev != '0')
								{}
								sem_post(&elec[i].mutex);
								pthread_exit(NULL);
								break;
							}
							else
								sem_post(&elec[i].mutex);
						}
						// continue;
					}
					else
					{
						printf("%s performing %c at electric stage for %d sec\n", inp->name, inp->ic, time1);
						fflush(stdout);
						flag = 1;
						sleep(time1);
						elec[idx].prev = '0';
						printf("%s performance at electric stage finished\n", inp->name);
						fflush(stdout);
						sem_post(&elec[idx].mutex);
						pthread_exit(NULL);
						break;
					}
				}
				else
				{
					int idx = -1;
					lp(i, 0, e)
					{
						if (elec[i].prev != 's' && elec[i].prev != '0')
						{
							sem_wait(&elec[i].mutex);
							// if (elec[i].prevtime > (time1 + 2))
							// {
							// 	elec[i].prev = 's';
							// }
							elec[i].prev = 's';
							idx = i;
							printf("%s joined %s's performance, performance extended by 2 secs\n", inp->name, elec[i].name);
							fflush(stdout);
							flag = 1;
							// sleep(time1);
							while (elec[i].prev != '0')
							{}
							sem_post(&elec[i].mutex);
							pthread_exit(NULL);
							break;
						}
						else
							sem_post(&elec[i].mutex);
					}
					if (idx == -1)
					{
						idx = checkelec(inp->name, inp->ic, time1);
						if (idx != -1)
						{
							printf("%s performing %c at electric stage for %d sec\n", inp->name, inp->ic, time1);
							fflush(stdout);
							flag = 1;
							sleep(time1);
							elec[idx].prev = '0';
							printf("%s performance at electric stage finished\n", inp->name);
							fflush(stdout);
							sem_post(&elec[idx].mutex);
							pthread_exit(NULL);
							break;
						}
					}
				}
			}
		}
		// printf("%scad\n", inp->name);
		time(&now);
		elapsed = difftime(now, begin);
		if ((elapsed > t) && (flag == 0))
		{
			printf("%s %c left because of impatience\n", inp->name, inp->ic);
			fflush(stdout);
			terminate = 0;
			pthread_exit(NULL);
			break;
		}
	}
	pthread_exit(NULL);
}
int main()
{
	scanf("%d %d %d %d %d %d %lf", &k, &a, &e, &c, &t1, &t2, &t);
	lp(i, 0, k)
	{
		scanf("%s %c %d", performers[i].name, &performers[i].ic, &performers[i].arrivaltime);
	}
	lp(i, 0, a)
	{
		acous[i].prev = '0';
		// acous[i].prevtime = 0;
		sem_init(&acous[i].mutex, 0, 2);
	}
	lp(i, 0, e)
	{
		elec[i].prev = '0';
		// elec[i].prevtime = 0;
		sem_init(&elec[i].mutex, 0, 2);
	}
	lp(i, 0, c)
	{
		coordinators[i].available = 1;
		pthread_mutex_init(&coordinators[i].lock, NULL);
	}
	lp(i, 0, k)
	{
		pthread_create(&per[i], NULL, allot, (void*)(&performers[i]));
	}
	lp(i, 0, k)
	{
		pthread_join(per[i], NULL);
	}
	lp(i, 0, a)
	{
		// acous[i].prev = '0';
		sem_destroy(&acous[i].mutex);
	}
	lp(i, 0, e)
	{
		// elec[i].prev = '0';
		sem_destroy(&elec[i].mutex);
	}
	printf("Finished\n");
	// lp(i,0,)
}