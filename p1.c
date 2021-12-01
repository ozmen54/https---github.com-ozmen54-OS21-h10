// İki proses koordinesiz
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

void foo1(){
        printf("A\n");
  /*
    while(1){
      printf("A\n");
      sleep(1);
    }
  */
}

void foo2(){
  sleep(5);
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
  
  pid = fork();
  if(pid == 0) {
    foo1();
  } else {
    foo2();
  }
  return 0;
}
