#include <stdio.h>
#include <time.h>
int task1(void);
int task2(void);
int task3(void);
bool release(void)
{
   clock_t start_t, end_t;
   start_t = clock();
   while(1){
     end_t = clock();
     total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
     if (total_t==1)
       return 1;
   }
}
int main() {
  clock_t start_t, end_t;
  int i=0;
   while(1)
   {
     if (release()=1 && i=0){
        task1();
       i=i+1
     }
     if(release()=1 && i=1){
        task2();
       i=i+1
         }
      if(release()=1 && i=2){
        task3();
        i=0;
   }
}
int task1(void)
{
    printf("task1 \n");
    return 0;
}
int task2(void)
{
    printf("task2 \n");
    return 0;
}
int task3(void)
{
    printf("task3 \n");
    return 0;
}
