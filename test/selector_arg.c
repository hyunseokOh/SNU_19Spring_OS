#define SYSCALL_ROTLOCK_WRITE 400
#define SYSCALL_ROTUNLOCK_WRITE 402

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static int selectorRun = 1;

void intHandler(int sig) {
  /* handle ctrl-c interrupt */
  selectorRun = 0;
}

int main(int argc, char *argv[]) {
  int num;
  long longNum;
  int degree;
  long longDegree;
  int range;
  long longRange;

  FILE *fp = NULL;
  char *endPtr = NULL;

  if (argc != 4) {
    printf("Example Usage: ./selector [starting num] [degree] [range] \n");
    return 0;
  }

  longNum = strtol(argv[1], &endPtr, 10);

  if (*endPtr) {
    /* endPtr points to NULL char only when the entire argument is a number */
    printf("INVALID ARGUMENT: invalid character exists or no digits at all\n");
    return 0;
  } else if (errno != 0) {
    /* errno is set to ERANGE if underflow or overflow occurs */
    printf("INVALID ARGUMENT: most likely overflow or underflow\n");
    return 0;
  } else if ((longNum > INT_MAX) || (longNum < INT_MIN)) {
    printf("INVALID ARGUMENT: number cannot be expressed as int'\n");
    return 0;
  } else {
    num = (int)longNum;
  }

  longDegree = strtol(argv[2], &endPtr, 10);

  if (*endPtr) {
    /* endPtr points to NULL char only when the entire argument is a number */
    printf("INVALID ARGUMENT: invalid character exists or no digits at all\n");
    return 0;
  } else if (errno != 0) {
    /* errno is set to ERANGE if underflow or overflow occurs */
    printf("INVALID ARGUMENT: most likely overflow or underflow\n");
    return 0;
  } else if ((longDegree > INT_MAX) || (longDegree < INT_MIN)) {
    printf("INVALID ARGUMENT: number cannot be expressed as int'\n");
    return 0;
  } else {
    degree = (int)longDegree;
  }

  longRange = strtol(argv[3], &endPtr, 10);

  if (*endPtr) {
    /* endPtr points to NULL char only when the entire argument is a number */
    printf("INVALID ARGUMENT: invalid character exists or no digits at all\n");
    return 0;
  } else if (errno != 0) {
    /* errno is set to ERANGE if underflow or overflow occurs */
    printf("INVALID ARGUMENT: most likely overflow or underflow\n");
    return 0;
  } else if ((longRange > INT_MAX) || (longRange < INT_MIN)) {
    printf("INVALID ARGUMENT: number cannot be expressed as int'\n");
    return 0;
  } else {
    range = (int)longRange;
  }

  signal(SIGINT, intHandler);

  while (selectorRun) {
    syscall(SYSCALL_ROTLOCK_WRITE, degree, range);
    fp = fopen("integer", "w");
    if (fp != NULL) {
      fprintf(fp, "%d\n", num);
      printf("selector: %d\n", num++);
      fclose(fp);
      fp = NULL;
    }
    syscall(SYSCALL_ROTUNLOCK_WRITE, degree, range);
  }

  if (fp != NULL) {
    fclose(fp);
    fp = NULL;
  }
}
