#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SYS_GET_GPS_LOCATION 399

char *google_prefix = "https://maps.google.com/?q=";

struct gps_location {
  int lat_integer;
  int lat_fractional;
  int lng_integer;
  int lng_fractional;
  int accuracy;
};

int main(int argc, char *argv[]) {
  int syscallResult;
  struct gps_location gps = { 0, 0, 0, 0, 0 };

  if (argc != 2) {
    printf("Must pass file path!\n");
    return 0;
  }

  syscallResult = syscall(SYS_GET_GPS_LOCATION, argv[1], &gps);

  if (syscallResult == -1) {
    if (errno == EACCES) {
      printf("Cannot access file %s\n", argv[1]);
    } else {
      printf("Oops! syscall returned -1, errno = %d\n", errno);
    }
    return 0;
  }

  printf("File path = %s\n", argv[1]);
  printf("Latitude = %d.%d, Longitude = %d.%d\n", gps.lat_integer, gps.lat_fractional, gps.lng_integer, gps.lng_fractional);
  printf("Accuracy = %d [m]\n", gps.accuracy); 
  printf("Google Link = %s%d.%d,%d.%d\n", google_prefix, gps.lat_integer, gps.lat_fractional, gps.lng_integer, gps.lng_fractional);
}
