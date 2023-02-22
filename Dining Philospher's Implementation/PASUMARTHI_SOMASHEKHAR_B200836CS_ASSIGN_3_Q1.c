#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<semaphore.h>

static volatile int counter = 0;
pthread_mutex_t soma;

void *thread_increment(void *c){
    //printf("%s : beginning of increment thread \n", (char*) c);
    int i = 0;
    while(i < 1e7){
        pthread_mutex_lock(&soma);
        counter = counter + 1;
        pthread_mutex_unlock(&soma);
        i++;
    }
    //printf("%d\n",counter);
    //printf("%s : Ending of the increment thread \n",(char*) c);
    return NULL;
}

void *thread_decrement(void *c){
    //printf("%s : beginning of decrement thread \n", (char*) c);
    int i = 0;
    while(i < 1e7){
        pthread_mutex_lock(&soma);
        counter = counter - 1;
        pthread_mutex_unlock(&soma);
        i++;
    }
    //printf("%d\n",counter);
    //printf("%s : Ending of decrement thread \n", (char*) c);
    return NULL;
}
int main(){
    pthread_t somashekhar_1;
    pthread_t somashekhar_2;

    int retVal;
    //printf("The Value of the counter before beginning : %d\n",counter);

    retVal = pthread_create(&somashekhar_1,NULL,thread_increment,"Thread_A");
    assert(retVal == 0);

    retVal = pthread_create(&somashekhar_2,NULL,thread_decrement,"Thread_B");
    assert(retVal == 0);
    

    retVal = pthread_join(somashekhar_1,NULL);
    assert(retVal == 0);

    retVal = pthread_join(somashekhar_2,NULL);
    assert(retVal == 0);
    printf("%d",counter);
    //printf("The Final Value of counter after Both process are done : %d\n",counter);
}