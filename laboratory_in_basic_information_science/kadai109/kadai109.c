#include <stdio.h>
 
char* mystrcat(const char*, const char*);

int main() {
  const char a[10] = {0};
  const char b[10] = {0};

  scanf("%s", a);
  scanf("%s", b);

  printf("%s\n", mystrcat(a, b));
  
  return 0;
}
