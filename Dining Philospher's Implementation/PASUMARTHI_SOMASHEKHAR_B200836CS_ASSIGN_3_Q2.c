#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<semaphore.h>
int n;
sem_t forks[5];
int left_fork(int p){ 
    return p; 
}
int right_fork(int p){
    return (p + 1)%5; 
}
void get_forks(int p) {
    if(n == 1){
        // Solution to avoid the deadlock situation
        if (p == 4){
            sem_wait(&forks[right_fork(p)]);
            printf("philosopher %d grabs %d(right fork)\n",p,right_fork(p));
            sem_wait(&forks[left_fork(p)]);
            printf("philosopher %d grabs %d(left fork)\n",p,left_fork(p));
        }
        else{
            sem_wait(&forks[left_fork(p)]);
            printf("philosopher %d grabs %d(left fork)\n",p,left_fork(p));
            sem_wait(&forks[right_fork(p)]);
            printf("philosopher %d grabs %d(right fork)\n",p,right_fork(p));
        }
    }
    else if(n == 0){
        // we might have a deadlock situation in this case
        sem_wait(&forks[left_fork(p)]);
        printf("philosopher %d grabs %d(left fork)\n",p,left_fork(p));
        sem_wait(&forks[right_fork(p)]);
        printf("philosopher %d grabs %d(right fork)\n",p,right_fork(p));
    }
}

void put_forks(int p){
    sem_post(&forks[left_fork(p)]);
    sem_post(&forks[right_fork(p)]);
    printf("philosopher %d ends eating and releases forks %d(left) and %d(right)\n",p,left_fork(p),right_fork(p));
}
void think(int p){
    printf("philosopher %d starts thinking\n",p);
    return;
}
void eat(int p){
    printf("philosopher %d starts eating\n",p);
    return;
}
void* philosopher1(void *c){
    while (1) {
        think(0);
        get_forks(0);
        eat(0);
        put_forks(0);
    }
}
void* philosopher2(void *c){
    while (1) {
        think(1);
        get_forks(1);
        eat(1);
        put_forks(1);
    }
}
void* philosopher3(void *c){
    while (1) {
        think(2);
        get_forks(2);
        eat(2);
        put_forks(2);
    }
}
void* philosopher4(void *c){
    while (1) {
        think(3);
        get_forks(3);
        eat(3);
        put_forks(3);
    }
}
void* philosopher5(void *c){
    while (1) {
        think(4);
        get_forks(4);
        eat(4);
        put_forks(4);
    }
}

int main(int argc,char *argv[]){
    for(int i = 0;i<5;i++){
        sem_init(&forks[i],0,1);
    }
    
    printf("To have deadlock situation Enter 0 \n");
    printf("To Avoid deadlock situation Enter 1\n");

    printf("Enter the number :\n");
    scanf("%d",&n);
    printf("Parent : Begin \n");
    pthread_t somashekhar_1;
    pthread_t somashekhar_2;
    pthread_t somashekhar_3;
    pthread_t somashekhar_4;
    pthread_t somashekhar_5;
    pthread_create(&somashekhar_1,NULL,philosopher1,"philosopher1");
    pthread_create(&somashekhar_2,NULL,philosopher2,"philosopher2");
    pthread_create(&somashekhar_3,NULL,philosopher3,"philosopher3");
    pthread_create(&somashekhar_4,NULL,philosopher4,"philosopher4");
    pthread_create(&somashekhar_5,NULL,philosopher5,"philosopher5");

    pthread_join(somashekhar_1,NULL);
    pthread_join(somashekhar_2,NULL);
    pthread_join(somashekhar_3,NULL);
    pthread_join(somashekhar_4,NULL);
    pthread_join(somashekhar_5,NULL);
    printf("Parent : End \n");
}