#include<stdio.h>
/* Compile this program into `child4' */
int i = 143;
int main()
{
    printf("child4 starts...\n");
    while(i != 245);
      printf("child4 outside loop...\n");
    return 0;
}
