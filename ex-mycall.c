#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int arg, r;

  arg = atoi(argv[1]);

  r = syscall(351, arg);

  if (r != 0)
    printf("Erro (%d). Execução terminada.\n", r);

  return 0;
}
  
  
