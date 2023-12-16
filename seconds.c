#include <stdio.h>
#include <time.h>
int main(){
    clock_t start_t, end_t, total_t;
    int i=0;
    start_t = clock();
    while(1){
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
         if (total_t==1){
            printf("%d\n",i);
            total_t=0;
            i=i+1;
            start_t = clock();
        }
   }
}
