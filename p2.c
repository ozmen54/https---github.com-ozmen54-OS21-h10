// İki proses koordinesiz
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
// Semafor için gerekli
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

  sem_t *semAdr;

void foo1(){
  sleep(2);
  printf("A\n");
  sem_post(semAdr);	
  /*
    while(1){
      printf("A\n");
      sleep(1);
    }
  */
}

void foo2(){
  //sleep(5);
  sem_wait(semAdr);
  printf("B\n");
  /*
    while(1){
      printf("B\n");
      sleep(3);
      }
*/
}


int main()
{
  int pid;

  
  semAdr = sem_open("sem", O_CREAT,0666,0);


  
  pid = fork();
  if(pid == 0) {
    foo1();
  } else {
    foo2();
  }
  return 0;
}
