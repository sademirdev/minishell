#include "testing.h"
#include <sys/wait.h>
#include <unistd.h>

int err = 0;
int err_in = 0;

void run_token_test(void);
void run_separator_test(void);

int main() {
  int pid = fork();

  if (pid == 0) {
    run_token_test();
  } else {
    waitpid(pid, NULL, 0);
    run_separator_test();
  }
}