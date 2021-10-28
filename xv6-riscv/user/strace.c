#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define ARG_MAX 32
int main(int argc, char *argv[])
{
  int i;

  if (argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9'))
  {
    fprintf(2, "Correct format: %s mask command arguments...\n", argv[0]);
    exit(1);
  }

  write(1, "Tracing calls...\n", 18);
  int mask = atoi(argv[1]);
  int call = 0;

  while (mask != 1)
  {
    mask = mask >> 1;
    call++;
  }

  if (trace(atoi(argv[1])) < 0)
  {
    fprintf(2, "%s: trace failed\n", argv[0]);
    exit(1);
  }

  char *new_argv[argc];

  for (i = 2; i < argc; i++)
  {
    new_argv[i - 2] = argv[i];
    //write(1, argv[i], strlen(argv[i]));
  }
  exec(new_argv[0], new_argv);
  exit(0);
}
