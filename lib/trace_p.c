#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

#include "trace_p.h"

int trace_p(void)
{
  int status;

  printf("exec %s? <y/n>: ", __func__);
  char is_exec = getchar();
  if (is_exec == 'n') return 0;
  else if (is_exec == 'y') ;
  else return 0;

  pid_t pid = getppid();

  printf("attach to %d\n", pid);

  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) < 0) {
    perror("failed to attach");
    exit(1);
  }

  while (1) {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      break;
    } else if (WIFSIGNALED(status)) {
      printf("terminated by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      printf("stopped by signal %d\n", WSTOPSIG(status));
    }

    ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
  }

  return 0;
}
