#include<stdio.h>
int main()
{
    int list[]={2,34,12,55,69,1,10,22,45,36,99,13,56};
    for(int i=0; i<sizeof(list);i++)
    {
        if(list[i]==search_n)
        {
            printf("Found %d at %d -th place",search_n,i);
            return 0;
        }
    }
}