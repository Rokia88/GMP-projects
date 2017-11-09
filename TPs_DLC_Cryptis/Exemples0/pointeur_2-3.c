
#include <stdio.h>

int main()
{
  short int a = 7;
  short int *pa;

 /* pa = (short int *) NULL;
  
  printf("pa = %u\n", pa);
  printf("pa = %p\n", pa);*/
  
// exception car pa pointe sur NULL, donc *pa n'a pas de sens
  printf("pa = %p ; *pa = %u ; a = %u\n", pa, *pa, a);
  pa = &a;
  printf("pa = %p ; *pa = %u ; a = %u\n", pa, *pa, a);
  *pa = 12;
  printf("pa = %p ; *pa = %u ; a = %u\n", pa, *pa, a);

return 0;
}
