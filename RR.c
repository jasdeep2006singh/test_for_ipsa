#include <stdio.h>
int task1(void);
int task2(void);
int task3(void);
int main() {
   while(1)
   {
        task1();
        task2();
        task3();
   }
}
int task1(void)
{
    printf("task1 \n");
}
int task2(void)
{
    printf("task2 \n");
}
int task3(void)
{
    printf("task3 \n");
}
