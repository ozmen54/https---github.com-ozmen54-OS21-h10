// İki proses koordinesiz
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
// Semafor için gerekli
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
// signal
#include<signal.h>

sem_t *semAdr1;
sem_t *semAdr2;

void foo1(){
  
    while(1){
      sem_wait(semAdr1);
      printf("A\n");
      sleep(1);
      sem_post(semAdr2);
    }
  
}

void foo2(){
  while(1){
    sem_wait(semAdr2);
    printf("B\n");
    sleep(1);
    sem_post(semAdr1);
  }

}

void termination(int a){
  sem_close(semAdr1);
  sem_close(semAdr2);
  sem_destroy(semAdr1);
  sem_destroy(semAdr1);
  printf("Temiz çıkış\n");
}


int main()
{
  int pid;
  // İsimli semaforlar (named semaphores)
  semAdr1 = sem_open("sem1", O_CREAT,0666,1);
  semAdr2 = sem_open("sem2", O_CREAT,0666,0);
  // Temiz çıkış: Çıkmadan önce semaforları kapat ve yoket.
  signal(SIGINT, termination);
  
  pid = fork();
  if(pid == 0) {
    foo1();
  } else {
    foo2();
  }

  return 0;
}
