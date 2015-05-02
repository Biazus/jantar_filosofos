#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

#define LEFT (ph_num+(N-1))%N
#define RIGHT (ph_num+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

//GLOBAL VARIABLES
sem_t * S;
sem_t mutex;
int * phil_num;
int * state;
pthread_t * thread_id;
int N;

void * philosophize(void *num);
void take_fork(int ph_num);
void release_fork(int ph_num);
void test_fork(int ph_num);

int main(){
    //VARIAVEIS
    int i=0, j=0;
    N=0;
    printf("Insira o numero de filosofos:\n");
    scanf("%d",&N);
    printf("\n");
    S=(sem_t *) malloc(N*sizeof(sem_t));
    phil_num=(int *) malloc(N*sizeof(int));
    state=(int *) malloc(N*sizeof(int));
    thread_id = (pthread_t *) malloc(N*sizeof(pthread_t));

    for(j=0;j<N;j++)
        phil_num[j]=j;
    
    //sem and phil creation

    sem_init(&mutex,0,1);
    
    for(i=0;i<N;i++)
        sem_init(&S[i],0,0);

    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philosophize,&phil_num[i]);
        printf("Filósofo %d chegou na sala de jantar.\n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
    
    free(phil_num);
    free(S);
    free(thread_id);
    free(state);

    return 0;
}
void *philosophize(void *num){
    int *i = num;
    int sleep_time = (rand() % (9 - 1)) + 1;
    while(1)
    {
        int *i = num;
        sleep(sleep_time);
        take_fork(*i);
        sleep(sleep_time);
        release_fork(*i);
    }
}

void take_fork(int ph_num){
    sem_wait(&mutex);
    state[ph_num] = HUNGRY;
    printf("Filósofo %d está com fome\n",ph_num+1);
    test_fork(ph_num);
    sem_post(&mutex);
    sem_wait(&S[ph_num]);
    sleep(1);
}

void release_fork(int ph_num){
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("Filósofo %d libera os garfos %d e %d \n",ph_num+1,LEFT+1,ph_num+1);
    printf("Filósofo %d está pensando\n",ph_num+1);
    test_fork(LEFT);
    test_fork(RIGHT);
    sem_post(&mutex);
}

void test_fork(int ph_num){
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[ph_num] = EATING;
        sleep(1);
        printf("Filósofo %d pega os garfos %d e %d\n",ph_num+1,LEFT+1,ph_num+1);
        printf("Filósofos %d está comendo\n",ph_num+1);
        sem_post(&S[ph_num]);
    }
}
