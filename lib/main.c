#include <stdio.h>
#include <stdlib.h>

#include "trace_p.h"
#include "trace_r.h"

int main(int argc, char *argv[])
{
  printf("Start main proccess\n");
  trace_p();
  trace_r();
  printf("End all proccess\n");
}
