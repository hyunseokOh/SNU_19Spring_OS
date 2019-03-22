#include <stdint.h> /* int64_t */
#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h> /* strtol */
#include <limits.h> /* INT_MAX, INT_MIN */
#include <errno.h> /* errno */
#include <sys/syscall.h> /* sycall method */
#include <sys/types.h>   /* declaration of pid_t, etc. */
#include <unistd.h>

#include <inttypes.h>

struct prinfo {
  int64_t state;          /* current state of process */
  pid_t pid;              /* process id */
  pid_t parent_pid;       /* process id of parent */
  pid_t first_child_pid;  /* pid of oldest child */
  pid_t next_sibling_pid; /* pid of younger sibling */
  int64_t uid;            /* user id of process owner */
  char comm[64];          /* name of program executed */
};

int main(int argc, char *argv[]) {
  int nr;
  int nrBefore;
  struct prinfo *buf = NULL;

  if (argc != 2) {
    printf("You need to pass nr as a command line argument!\n");
    return 0;
  }

  /* Convert command line argument to nr  */
  long convertedNum;
  char *endPtr = NULL;
  convertedNum = strtol(argv[1], &endPtr, 10);

  if(*endPtr){ // endPtr points to NULL char only when the entire argument is a number
    printf("INVALID ARGUMENT: invalid character exists or no digits at all\n");
    return 0;
  }
  else if(errno != 0){ // errno is set to ERANGE if underflow or overflow occurs
    printf("INVALID ARGUMENT: most likely overflow or underflow\n");
    return 0;
  }
  else if((convertedNum > INT_MAX) || (convertedNum < INT_MIN)){
    printf("INVALID ARGUMENT: number cannot be expressed as int'\n");
    return 0;
  }
  else{
    nr = (int)convertedNum;
    nrBefore = nr;
  }

//  nr = atoi(argv[1]); // use of atoi is depreciated due to lack of error-handling
//  nrBefore = nr;

/* commented out on purpose to check error-handling of ptree */
//  if (nr < 0) {
//    printf("nr should be a positive number\n");
//    return 0;
//  }

  printf("Requested nr: %d\n", nr);

  buf = (struct prinfo *)malloc(sizeof(struct prinfo) * nr);

    int64_t syscallResult = 
//  long int syscallResult =
      syscall(398, buf, &nr);

  for (int i = 0; i < nr; i++) {
    struct prinfo p = buf[i];
    printf("%s,%d,%lld,%d,%d,%d,%lld\n", p.comm, p.pid, p.state, p.parent_pid,
           p.first_child_pid, p.next_sibling_pid, p.uid);
  }

  printf("value of nr before: %d, after: %d\n", nrBefore, nr);
  printf("System call sys_ptree returned %" PRId64 "\n", syscallResult);

  printf("TEST END\n");

  free(buf);
  return 0;
}
