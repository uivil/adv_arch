#include <stdio.h>


/*
void gen(int n, int add_prev, int prev_num, int prev_level, int level)
{
  int nodes = n  + add_prev;
  if (nodes == 1) {
    printf("l%d_%d ", 1, level);
    return;
  }
  
  for (int i=0; i<n; ++i)
    printf("l%d_%d ", i+1, level);

  
  if (!add_prev && (n & 1)) {
    prev_num = n;
    prev_level = level;
  }

  if (add_prev && (n & 1))
      printf("l%d_%d ", prev_num, prev_level);

  printf("\n");

  if (nodes & 1)
    gen(nodes/2, 1,prev_num,prev_level, level + 1);
  else
    gen(nodes/2, 0,prev_num, prev_level, level + 1);
    
}
*/

int x;
int lx = 0;
int a = 0;

void gen(int n, int level, int cin)
{
  //printf("x=%d", x);
  //getchar();
  int nodes = n + cin;
  if (nodes == 1)  return;
  int len = ((n & 1) && n > 1) ? n - 1 : n;

  if ((n & 1) && !cin) {
    x = n;
    lx = level;
    a = 1;
  }
  for (int i=0; i<len && len > 1; i +=2)
    printf("add(l%d_%d, l%d_%d -> l%d_%d) ", i+1, level, i+2, level, i/2+1, level+1);
  
  if (cin &&  !!(n & 1) && a == 1) {
    a = 0;
    printf("add(l%d_%d, l%d_%d -> l%d_%d) ", n, level, x, lx, n/2+1, level+1);
  }


  printf("\n"); 

  
  if (nodes & 1)
    gen(nodes/2, level + 1, 1);
  else {
    gen(nodes/2, level + 1, 0);
  }




}




int main()
{
  int n = 10;

  gen(n, 1, 0);


  return 0;
}
