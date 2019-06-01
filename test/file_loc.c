#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SYS_GET_GPS_LOCATION 399

static inline double to_double(int integer, int fractional) {
  return (double) integer + (double) fractional * 1e-6;
}

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
  double lat;
  double lng;
  struct gps_location gps = { 0, 0, 0, 0, 0 };

  if (argc != 2) {
    printf("Must pass file path!\n");
    return 0;
  }

  syscallResult = syscall(SYS_GET_GPS_LOCATION, argv[1], &gps);

  if (syscallResult == -1) {
    if (errno == EACCES) {
      printf("Cannot access file %s\n", argv[1]);
    } else if (errno == EINVAL) {
      printf("Invalid argument\n");
    } else if (errno == ENOMEM) {
      printf("Memory allocation failed\n");
    } else if (errno == ENOENT) {
      printf("No file entry\n");
    } else if (errno == EFAULT) {
      printf("Copy to user (kernel) failed\n");
    } else if (errno == ENODEV) {
      printf("Not gps tagged\n");
    } else {
      printf("Oops! Unknown error, errno = %d\n", errno);
    }
    return 0;
  }

  lat = to_double(gps.lat_integer, gps.lat_fractional);
  lng = to_double(gps.lng_integer, gps.lng_fractional);

  printf("File path = %s\n", argv[1]);
  printf("Latitude = %.6lf, Longitude = %.6lf\n", lat, lng);
  printf("Accuracy = %d [m]\n", gps.accuracy); 
  printf("Google Link = %s%.6lf,%.6lf\n", google_prefix, lat, lng);
}
