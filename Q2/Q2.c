#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define lp(i,a,b) for(int i=a;i<b;i++)
#define rlp(i,a,b) for(int i=b;i>=a;i--)
typedef struct pcomp {
	int name;
	int w;
	int r;
	int p;
	float x;
} pcomp;
typedef struct vzone {
	int name;
	int k;
	int slots;
	pthread_mutex_t lock;
	int prob;
} vzone;
typedef struct student {
	int name;
	char isvaccinated;
	int tries;
	// int probab;
} student;
int min(int a, int b)
{
	return a > b ? b : a;
}
int n, m, o, waiting;
pcomp pcomps[105];
vzone vzones[105];
student students[105];
pthread_t pcs[105];
pthread_t vzn[105];
pthread_t studs[105];
int genrandom(int lower, int upper)
{
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}
void *func3(void *x)
{
	student* inp = (student*) x;
	printf("Student %d has arrived for his 1st round of vaccination\n", inp->name);
	sleep(0.5);
	printf("Student %d is waiting to be allocated a slot on a Vaccination Zone\n", inp->name);
	int flag = 0;
	while (flag == 0)
	{
		if (inp->isvaccinated == 0 && inp->tries == 2)
		{
			printf("Student %d sent to home!! sed lyf\n", inp->name);
			waiting--;
			break;
		}
		lp(i, 0, m)
		{
			if (vzones[i].slots > 0)
			{
				pthread_mutex_lock(&vzones[i].lock);
				printf("Student %d assigned a slot on the Vaccination Zone %d and waiting to be vaccinated\n", inp->name, vzones[i].name);
				sleep(1);
				flag = 1;
				vzones[i].slots--;
				printf("Student %d on Vaccination Zone %d has been vaccinated which has success probablity %d%%\n", inp->name, vzones[i].name, vzones[i].prob);
				int randpro = genrandom(1, 100);
				if (randpro >= vzones[i].prob)
				{
					printf("Student %d has tested positive for antibodies\n", inp->name);
					waiting--;
					inp->isvaccinated = 1;
					// flag = 1;
					pthread_mutex_unlock(&vzones[i].lock);
					break;
				}
				else
				{
					printf("Student %d has tested negative for antibodies\n", inp->name);
					inp->isvaccinated = 0;
					inp->tries++;
					flag = 0;
					if (inp->tries == 0)
					{
						printf("Student %d has arrived for his 2nd round of vaccination\n", inp->name);
						printf("Student %d is waiting to be allocated a slot on a Vaccination Zone\n", inp->name);
					}
					else if (inp->tries == 1)
					{
						printf("Student %d has arrived for his 3rd round of vaccination\n", inp->name);
						printf("Student %d is waiting to be allocated a slot on a Vaccination Zone\n", inp->name);
					}
					else if (inp->tries == 2)
					{
						pthread_mutex_unlock(&vzones[i].lock);
						break;
					}
				}
				pthread_mutex_unlock(&vzones[i].lock);
			}
		}
	}
	// if (waiting == 0)
	// {
	// 	printf("Simulation Ends here\n");
	// 	exit(0);
	// }
}
void *func2(void *x)
{
	// printf("adwwad\n");
	vzone* inp = (vzone*) x;
	while (1)
	{
		if (waiting == 0)
		{
			pthread_exit(NULL);
		}
		while ((inp->k) <= 0)
		{}
		if (waiting == 0)
		{
			pthread_exit(NULL);
		}
		printf("Vaccination Zone %d entering Vaccination Phase\n", inp->name);
		sleep(0.5);
		int temp = inp->k;
		int slots = min(8, min(temp, waiting));
		if (slots == 0)
		{
			printf("Vaccination Zone %d has run out of vaccines\n", inp->name);
			continue;
		}
		printf("Vaccination Zone %d is ready to vaccinate with %d slots\n", inp->name, slots);
		inp->slots = slots;
		while (waiting > 0 && inp->slots > 0)
		{}
		if (waiting == 0)
		{
			pthread_exit(NULL);
		}
	}
}
void *func(void* x)
{
	pcomp* inp = (pcomp*) x;
	while (1)
	{
		inp->w = genrandom(2, 5);
		inp->r = genrandom(1, 5);
		inp->p = genrandom(10, 20);
		printf("Pharmaceutical Company %d is preparing %d batches of vaccines which have success probablity %.2f\n", inp->name, inp->r, inp->x);
		sleep(inp->w);
		printf("Pharmaceutical Company %d has prepared %d batches of vaccines which have success probablity %.2f\n", inp->name, inp->r, inp->x);
		printf("Waiting for all the vaccines to be used to resume production\n");
		// pthread_mutex_lock(&mut3);
		if (waiting == 0)
		{
			pthread_exit(NULL);
		}
		int cou = inp->r;
		lp(i, 0, cou)
		{
			int flag = 0;
			lp(j, 0, m)
			{
				pthread_mutex_lock(&vzones[j].lock);
				if (vzones[j].k == 0)
				{
					printf("Pharmaceutical Company %d is delivering a vaccine batch to Vaccination Zone %d which has success probablity %.2f\n", inp->name, vzones[j].name, inp->x);
					sleep(0.5);
					int x = genrandom(1, 8);
					// vzones[i].slots = min(x, waiting);
					vzones[j].k = inp->p;
					flag = 1;
					vzones[j].prob = 100 * (inp->x);
					printf("Pharmaceutical Company %d has delivered vaccines to Vaccination zone %d, resuming vaccinations now\n", inp->name, vzones[j].name);
					pthread_mutex_unlock(&vzones[j].lock);
					break;
				}
				pthread_mutex_unlock(&vzones[j].lock);
			}
			if (flag == 0)
				i--;
		}
	}
	// pthread_mutex_unlock(&mut3);
}
int main()
{
	printf("Enter the number of pharmaceutical companies:-\n");
	scanf("%d", &n);
	printf("Enter the probablities of the pharmaceutical companies one by one\n");
	lp(i, 0, n)
	{
		scanf("%f", &pcomps[i].x);
		pcomps[i].name = i + 1;
		pcomps[i].w = 0;
		pcomps[i].r = 0;
		pcomps[i].p = 0;
		// printf("%d %d %d\n", pcomps[i].w, pcomps[i].r, pcomps[i].p);
	}
	printf("Enter the number of vaccination zones:-\n");
	scanf("%d", &m);
	// printf("Enter the names of the vaccination zones one by one\n");
	lp(i, 0, m)
	{
		// scanf("%d", vzones[i].name);
		vzones[i].name = i + 1;
		vzones[i].prob = 0;
		vzones[i].k = 0;
		pthread_mutex_init(&vzones[i].lock, NULL);
	}
	printf("Enter the number of students:-\n");
	scanf("%d", &o);
	waiting = o;
	// printf("Enter the names of the students one by one\n");
	lp(i, 0, o)
	{
		// scanf("%d", students[i].name);
		students[i].name = i + 1;
		students[i].isvaccinated = 0;
		students[i].tries = -1;
	}
	lp(i, 0, n)
	{
		pthread_create(&pcs[i], NULL, func, (void*)(&pcomps[i]));
	}
	lp(i, 0, m)
	{
		pthread_create(&vzn[i], NULL, func2, (void*)(&vzones[i]));
	}
	lp(i, 0, o)
	{
		pthread_create(&studs[i], NULL, func3, (void*)(&students[i]));
	}
	lp(i, 0, o)
	{
		pthread_join(studs[i], NULL);
	}
	lp(i, 0, m)
	{
		pthread_mutex_destroy(&vzones[i].lock);
	}
	printf("Simulation over\n");
}