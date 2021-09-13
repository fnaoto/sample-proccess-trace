#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "trace_r.h"

int trace_r(void)
{
  int status;

  printf("exec %s? <y/n>: ", __func__);
  char is_exec = getchar();
  if (is_exec == 'n') return 0;
  else if (is_exec == 'y') ;
  else return 0;

  pid_t pid = getppid();

  printf("attach to %d\n", pid);

  struct user_regs_struct regs;

  printf("%d\n", SYS_write);

  while (1) {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      break;
    } else if (WIFSTOPPED(status)) {
      ptrace(PTRACE_GETREGS, pid, NULL, &regs);
      printf("%lld %lld %lld %lld\n", regs.orig_rax, regs.rsi, regs.rdx, regs.rdi);
    }
    ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
  }

  return 0;
}
