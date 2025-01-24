#include "libraries.h"

int err(){
  printf("err %d\n",errno);
  printf("%s\n",strerror(errno));
  exit(1);
}
