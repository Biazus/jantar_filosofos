/*
 * Names: Felipe bueno da Rosa
 *       Miller Biazus
 *       Pedro Henrique Frozi de Castro e Souza
 *
 * Operating Systems 2 - Professor Alberto Egon Schaeffer Filho
 *
 * Dining Philosophers Single File Solution for N philosophers - Using semaphores
 *
 * In order to properly run the solution, use: 
 *
 *      $ gcc -o dining dining.c -pthread
 *      $ ./dining -n <number_of_philosophers>
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

/*CONSTANTS  */
#define LEFT (ph_num+(N-1))%N
#define RIGHT (ph_num+1)%N
#define THINKING 'T' 
#define HUNGRY 'H'
#define EATING 'E'

/*VARIABLES  */
sem_t * S;
sem_t mutex;
int * phil_num;
int * aging_vec;
char * state;
pthread_t * thread_id;
int N, TIME, aging;

/*FUNC DECLARATIONS  */
void * philosophize(void *num);
void take_fork(int ph_num);
void release_fork(int ph_num);
void test_fork(int ph_num);
void update_aging();

int main(int argc, char* argv[]){
    int i=0, j=0;
    N=0;
    aging=0;

    /*GETTING PARAMETER*/
    if(argc < 3) {
          printf("Utilizar:\n");
          printf("./dining -n <numero de filosofos>\n");
          exit(1);
     }
     for(i=1; i<argc; i++) {
          if(argv[i][0]=='-') {
                switch(argv[i][1]) {
                     case 'n': 
                          i++;
                          N = atoi(argv[i]);
                          break;
                     default:
                          printf("Parametro invalido: %s\n",argv[i]);
                          exit(1);
                }
          } else {
              printf("Parametro %d: %s invalido\n",i, argv[i]);
                exit(1);
          }
     }

    S=(sem_t *) malloc(N*sizeof(sem_t));
    phil_num=(int *) malloc(N*sizeof(int));
    state=(char *) malloc(N*sizeof(char));
    thread_id = (pthread_t *) malloc(N*sizeof(pthread_t));
    aging_vec=(int *) malloc(N*sizeof(int));

    for(j=0;j<N;j++)
        phil_num[j]=j;
    
    sem_init(&mutex,0,1);
    
    for(i=0;i<N;i++)
        sem_init(&S[i],0,0);

    for(i=0;i<N;i++)
        state[i]= THINKING;
    
    for(i=0;i<N;i++)
        aging_vec[i]= 0;

    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philosophize,&phil_num[i]);
        printf("Filósofo %d chegou na sala de jantar.\n",i+1);
    }
    printf("\n");
    
    /* PRINTING INITIAL STATE*/
    int k;
    for(k=0;k<N;k++)
        printf("%c ", state[k]);
    printf("\n");

    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
    
    /* MEMORY DEALLOCATION*/
    free(phil_num);
    free(S);
    free(thread_id);
    free(state);

    return 0;
}


/*FUNC DEFINITIONS*/
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
    //printf("Filósofo %d está com fome\n",ph_num+1);

    int k;
    for(k=0;k<N;k++)
        printf("%c ", state[k]);

    printf("\n");

    test_fork(ph_num);
    sem_post(&mutex);
    sem_wait(&S[ph_num]);
    sleep(1);
}

void release_fork(int ph_num){
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    //printf("Filósofo %d libera os garfos %d e %d \n",ph_num+1,LEFT+1,ph_num+1);
    //printf("Filósofo %d está pensando\n",ph_num+1);
    
    aging_vec[ph_num]=0;
    int k;
    for(k=0;k<N;k++)
        printf("%c ", state[k]);
    
    printf("\n");

    if(aging_vec[aging]>2)
        test_fork(aging);
    
    test_fork(LEFT);
    test_fork(RIGHT);
    sem_post(&mutex);
    update_aging();
}

void test_fork(int ph_num){
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING && ((aging_vec[LEFT] < 3 && aging_vec[RIGHT] < 3) || aging == ph_num))
    {
        
        state[ph_num] = EATING;
        sleep(1);
        //printf("Filósofo %d pega os garfos %d e %d\n",ph_num+1,LEFT+1,ph_num+1);
        //printf("Filósofos %d está comendo\n",ph_num+1);

        int k;
        for(k=0;k<N;k++)
            printf("%c ", state[k]);
        
        printf("\n");
        aging_vec[ph_num]=0;
        sem_post(&S[ph_num]);
    }
    else{
        aging_vec[ph_num]++;
//        if(aging_vec[ph_num]>aging_vec[aging])
//            aging=ph_num;
    }
    update_aging();
}

void update_aging(){
    int y = 0;
    for(y=0;y<N;y++){
        if(aging_vec[y]>aging_vec[aging])
        aging = y;
    }
}
