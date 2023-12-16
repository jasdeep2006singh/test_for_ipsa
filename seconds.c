#include <stdio.h>
#include <time.h>
int main(){
    clock_t start_t, end_t, total_t;
    start_t = clock();
    while(1){
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
         if (total_t==1){
            print("%d\n",total_t);
            total_t=0;
            start_t = clock();
        }
   }
}
