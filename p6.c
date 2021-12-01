#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;
#define  MAX_THREAD 2

void *foo1(void *a){
  int tid = *(int *)a;
  //while(1){
  sleep(2);
  printf("Burası A, thread %d\n",tid);
    sem_post(&sem);
    //}
}

void *foo2(void *a){
  int tid = *(int *)a;
  //while(1){

    sem_wait(&sem);
    printf("Burası B, thread %d\n",tid); 
    //}
}

int main()
{
  int ret;
  pthread_t tid[MAX_THREAD];
  pthread_attr_t attr;
  int a[2];
  void *res;

  
  sem_init(&sem, 0, 0);
  
  pthread_attr_init(&attr);
  
  a[0] = 1;
  ret = pthread_create(&tid[0], &attr, foo1, (void *)&a[0]);
  a[1] = 2;
  ret = pthread_create(&tid[1], &attr, foo2, (void *)&a[1]);


  pthread_join(tid[0], &res);
  pthread_join(tid[1], &res);
}
