#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

void usage(char *prog_name, char *filename) {
  printf("udage: %s <add data in %s>\n", prog_name, filename);
  exit(0);
}

void fatal(char *);

void *ec_malloc(unsigned int);

void fatal(char *message) {
  char error_message[100];
  strcpy(error_message, "[!!] fatal error: ");
  strncat(error_message, message, 79);
  perror(error_message);
  exit(-1);
}

void *ec_malloc(unsigned int size) {
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL)
    fatal("error occued to allocation memory in ec_malloc().\n");
  return ptr;
}

int main(int argc, char *argv[]) {
  int fd;
  char *buffer, *datafile;

  buffer = (char *)ec_malloc(100);
  datafile = (char *)ec_malloc(20);
  strcpy(datafile, "/tmp/notes");

  if (argc < 2)
    usage(argv[0], datafile);

  strcpy(buffer, argv[1]);

  printf("[DEBUG] buffer    @ %p: \'%s\'\n", buffer, buffer);
  printf("[DEBUG] datafile  @ %p: \'%s\'\n", datafile, datafile);

  strncat(buffer, "\n", 1);

  fd = open(datafile, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
  if (fd == -1)
    fatal("in main(), error occued to open in file.\n");
  printf("[DEBUG] file descriptor:%d\n", fd);

  if (write(fd, buffer, strlen(buffer)) == -1)
    fatal("in main(), error occured to write buffer in file.\n");

  if (close(fd) == -1)
    fatal("in main(), error occured to close in file.\n");

  printf("saved.\n");
  free(buffer);
  free(datafile);
}
